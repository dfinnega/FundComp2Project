//This file contains all of the functions that will be used to animate the mushroom

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <string>
#include "mushroom.h"
#include "globalVars.h"

using namespace std;

Mushroom::Mushroom( int startX, int startY){
   //initialze variables
   mPosX = startX;
   mPosY = startY;
   initY = startY;

   //initialize hitbox
   hitBox.x = mPosX+5;
   hitBox.y = mPosY;
   hitBox.h = blockSize;
   hitBox.w = blockSize-5;

   spriteLocation.x = mPosX;
   spriteLocation.y = mPosY;
   spriteLocation.w = blockSize;
   spriteLocation.h = blockSize;

   //velocities
   mVelX = 0;
   mVelY = 0;

   active = 0;
   goinUp = 0;
   hitCount = 0;

   frame = 0;
   initSprite();
   objectSpriteClips[0].x = 180;
   objectSpriteClips[0].y = 30;
   objectSpriteClips[0].h = 20;
   objectSpriteClips[0].w = 20;
}

void Mushroom::move(SDL_Rect* camera){
   if(mPosX >= camera->x && mPosX <= camera->x+SCREEN_WIDTH && active){
      if(mPosY >= initY-blockSize && goinUp){
        mVelY = -3; //rise out of
         mVelX = 0;
         if(mPosY == initY-blockSize) goinUp = 0;
      }
      mPosX += mVelX;
      mPosY += mVelY;
   }
   hitBox.x = mPosX+5;
   hitBox.y = mPosY;
   spriteLocation.y = mPosY;
   spriteLocation.x = mPosX-camera->x;

   mVelY = 1; //assume mushroom is always falling
   mVelX = 3;
}

void Mushroom::mapCollision(int camerax, SDL_Rect object){
   int shroomRight = hitBox.x;
   int shroomLeft = hitBox.x+hitBox.w;
   int shroomTop = hitBox.y;
   int shroomBottom = hitBox.y+hitBox.h;
   //object sides
   int Oright = object.x;
   int Oleft = object.x+object.w;
   int Otop = object.y;
   int Obottom = object.y+object.h;

   //check left and right collisions
   if( (shroomRight >= Oleft && shroomLeft < Oleft ) || (shroomLeft <= Oright && shroomRight > Oright)){
      if( (shroomBottom >= Otop && shroomTop < Otop) || (shroomTop <= Obottom &&shroomBottom > Obottom) ){
         mPosX-=mVelX;
         mVelX*=(-1);
      }
    }

   //check if collide with ground
   if(shroomBottom >= Otop && shroomTop <= Otop){
//cout<<"got a top collision"<<endl;
      if( (shroomRight >= Oleft && shroomLeft <= Oleft) || (shroomLeft <= Oright && shroomRight >= Oright) ){
cout<<"got  real a top collision"<<endl;
         mVelY = 0;
      }
   }
}

void Mushroom::render(int camX, int camY){
   if(mPosX >= camX && mPosX <= camX+SCREEN_WIDTH && active){
       SDL_RenderCopy(gRenderer, itemSheet, &objectSpriteClips[frame], &spriteLocation);
   }
}

int Mushroom::getPosX(){
   return mPosX;
}

int Mushroom::getPosY(){
   return mPosY;
}

SDL_Rect Mushroom::getHitBox(){
  return hitBox;
}

bool Mushroom::isActive(){
   return active;
}

void Mushroom::initSprite(){
   for(int i = 0; i <1; i++){
      objectSpriteClips[i].x = 100;
      objectSpriteClips[i].y = 100;
      objectSpriteClips[i].w = 20;
      objectSpriteClips[i].h = 20;
   }
}

void Mushroom::marioCollision(int cameraX, SDL_Rect mario){
   bool collisionFlag = 1; //assume a collision
   if(hitBox.y+hitBox.h <= mario.y ) collisionFlag = 0;
   if(hitBox.y >= mario.y+mario.h) collisionFlag = 0;
   if(hitBox.x+hitBox.w <= mario.x) collisionFlag = 0;
   if(hitBox.x >= mario.x+mario.w) collisionFlag = 0;

   if(collisionFlag == 1) {
      hitCount++;
      if(hitCount == 1){
         cout<<"hit by mario"<<endl;
         active = 1;
         goinUp = 1;
      } else{
         active = 0;
      }
   }
}
