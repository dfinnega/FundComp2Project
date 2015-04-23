#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
#include "goomba.h"
using namespace std;

Goomba::Goomba( int startX, int startY): Enemy( startX, startY){
   spriteNum = 3;
   spriteXInit = 0;
   spriteYInit = 0;
   spriteW = 17;
   spriteH = 20;
   spriteOffset = 30;
   initSprite();
   alive = 1;

}

void Goomba::move(SDL_Rect* camera){
   //move the enemy loeft or right
   if( mPosX >= camera->x && mPosX <=camera->x+SCREEN_WIDTH){
      mPosX += mVelX;

   //if object reaches the end of the screen then bounce back
      if( (mPosX + ENEMY_WIDTH > LEVEL_WIDTH) || (mPosX < 0) ){
         mVelX*=(-1);
      }
      
      //move the enemy vertifcally
      mPosY+=mVelY;

      frame++; //each time move is called, proress goombas frame count
      decideFrame(); //decide what frame  the sprite should be on
                          //this will differentiate for 
                          //different enemies
   }
   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

   mVelY = 5; //assume goomba is always falling

}

void Goomba::decideFrame(){
   if(alive){
      if((frame/frameDelay) >= (spriteNum - 1)){
         frame = 0;
      }
   }else{
      frame = 10; //this should make the sprite the squish
   }

}

int Goomba::marioCollision(int cameraX, SDL_Rect  mario){

if(mPosX >= cameraX && mPosX < cameraX+SCREEN_WIDTH){

   //for readability
   //enemy coordinates
   int enemyTop = mPosY;
   int enemyBottom = mPosY+blockSize;
   int enemyLeft = mPosX;
   int enemyRight = mPosX+blockSize;
   //mariocoordinate
   int Mtop = mario.y;
   int Mbottom = mario.y+blockSize;
   int Mleft = mario.x;
   int Mright = mario.x+blockSize;
 
  //The enemy is _____ Mario
   int above = 0, below = 0, right = 0, left = 0;
   if(enemyTop > Mbottom) below = 1; //enemy is below mario
   if(enemyBottom < Mtop) above = 1; //enemy is above mario
   if(enemyLeft > Mright) right = 1; //enemy is right of mario
   if(enemyRight < Mleft) left = 1; //enemy is left of mario
   if( above || below || left || right){
      return 0; //There is no collision
cout<<"no collision"<<endl;
   }

   //Check if mario is on top of enemy
   //aka if enemy has bottom collision with 
   //mario 
   if(enemyTop <= Mbottom && enemyBottom > Mbottom && alive){
cout<<"top part detected"<<endl;
      if(!left && !right){
         alive = 0;
         mPosX -=mVelX;
         mVelX = 0;
         cout<<"Mario hit top of goomba!"<<endl;
      }
   }
   }
}
