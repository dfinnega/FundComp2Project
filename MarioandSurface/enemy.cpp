#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
using namespace std;

Enemy::Enemy( int startX, int startY ){
        //nitializes the positions
        mPosX = startX;
        mPosY = startY;
	//cout << "mPosY=" << mPosY << endl;
        hitBox.x = mPosX;
        hitBox.y = mPosY-40;
        hitBox.h = blockSize;
        hitBox.w = blockSize;

        //movement of enemies
        mVelX = -1;
        mVelY = 5; //enemy will be moving downward

        //clip sprite sheet
        frame = 0;
        frameDelay = 4; 

        //enemy is initially alive
        alive = 1;

	loadTexture("smb_enemies_sheet.bmp");
}

void Enemy::render(int camX, int camY){
   //show the dot
   if( mPosX >= camX && mPosX <= camX+SCREEN_WIDTH){
      enemyTexture.render(mPosX - camX, mPosY - camY, &enemySpriteClips[frame/4]);
      //cout << camY << " " << mPosY << endl;
   }
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
SDL_Rect Enemy::getHitBox(){
   return hitBox;
}
void Enemy::mapCollision(int camerax, SDL_Rect object){
   //left and right collisions
   if( ( (mPosX+hitBox.w >= object.x) && (mPosX < object.x) ) || ( (mPosX <= object.x+object.w)  &&  (mPosX+hitBox.w > object.x+object.w) ) ){ 
      if(  ((mPosY+hitBox.h > object.y) || ( (mPosY) > (object.y) ) ) && ( (mPosY+hitBox.h < (object.y + object.h)) || ( (mPosY) < (object.y + object.h) ) )   ) {
       //cout<<mPosY<<" "<<mPosY+hitBox.h<<" "<<object.y<< " "<<object.y+object.h<<" "<<endl;
       mPosX -=mVelX;
       mVelX*=(-1);
      }
   }

   //collide.check if on ground
   if( mPosY+hitBox.h >= object.y && mPosY < object.y){
      if( !(mPosX+hitBox.w < object.x) && !(mPosX > object.x+object.w) ){
cout<<"enemy is ontop of something"<<endl;
cout<<mPosY+hitBox.h<<" "<<object.y<<" "<<mPosY<<endl;
         //mPosY = object.y-blockSize; //keep goomba on top of block
         //mPosY-=mVelY; //move it back to where it was
         mVelY = 0; //don't want to fall
      }
   }
}
