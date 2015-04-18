#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
using namespace std;

const int LEVEL_WIDTH = 2040;
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 540;
//const int blockSize = 40;


Enemy::Enemy(int num , int x, int y, int w, int h, int offset ){
        //nitializes the offsets
        mPosX = 200;
        mPosY = 420;
        //initialzes the velocity
        mVelX = 5;
        mVelY = 0;

        //clip sprite sheet
        spriteNum = num;
        spriteXInit = x;
        spriteYInit = y;
        spriteW = w;
        spriteH = h;
        spriteOffset = offset;
        initSprite();
        frame = 0;

}

void Enemy::move(SDL_Rect* camera){
   //move the enemy loeft or right
   mPosX += mVelX;

   //object can't go back in map
   if( mPosX < camera->x ){
      //run into wall basically
     mVelX = 0;
   }
   //if object reaches the end of the camera screen then bounce back
   if(mPosX + ENEMY_WIDTH > camera->x+camera->w){
      mVelX*=(-1);
   }

   //move the enemy up or down
   mPosY += mVelY;
   //if the enemy went too far up or down
   if( (mPosY < 0) || (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT) ){
      //move back
      mPosY -= mVelY*(-1);
   }

   frame++; //each time move is called, proress goombas frame count
   frame = decideFrame(); //decide what frame  the sprite should be on
                          //this will differentiate for 
                          //different enemies
}

void Enemy::render(int camX, int camY){
   //show the dot
   enemyTexture.render(mPosX - camX, mPosY - camY, &enemySpriteClips[frame/2]);
}

int Enemy::getPosX(){
   return mPosX;
}

int Enemy::getPosY(){
   return mPosY;
}

bool Enemy::loadTexture(std:: string path){
   //use function already in existence in Ltexture class
   return enemyTexture.loadFromFile(path);

}

void Enemy::initSprite(){
   for(int i = 0; i < spriteNum; i++){
      enemySpriteClips[i].x = spriteXInit + i*(spriteOffset);
      enemySpriteClips[i].y = spriteYInit;
      enemySpriteClips[i].w = spriteW;
      enemySpriteClips[i].h = spriteH; 
   }
}

int Enemy::decideFrame(){
   if((frame/2) >= (spriteNum - 1)){
      frame = 0;
   }
   return frame;
}
