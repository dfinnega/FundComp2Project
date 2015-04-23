#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
#include "koopa.h"
using namespace std;

Koopa::Koopa( int startX, int startY): Enemy( startX, startY){
	//koopas are basic too, nothing else special to them
   spriteNum = 4;
   spriteXInit = 150;
   spriteYInit = 0;
   spriteW = 17;
   spriteH = 23;
   spriteOffset = 30;
   initSprite();
}

void Koopa::move(SDL_Rect *camera){
   //move enemy to the left or right
   if( mPosX >= camera->x && mPosX <= camera->x+SCREEN_WIDTH){
      mPosX += mVelX;

      //if object reaches the end of the screen then change direction
      //this set up will be used for object collision
      if( (mPosX + ENEMY_WIDTH > LEVEL_WIDTH) || (mPosX < 0) ){
         mVelX *=(-1);
      }

      frame++;
      decideFrame();

   }   

   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

}

void  Koopa::decideFrame(){
   if(mVelX < 0){
      if( (frame/frameDelay) >= (spriteNum-2)){
         frame = 0;
      }
   } if(mVelX >= 0){
      if( (frame/frameDelay) >= spriteNum){
         frame = 2*frameDelay;//4 is the delay number
                     //if went back to 2 it would be on
                     //sprite 0 actually
      }
   }
}

int Koopa::marioCollision(int, SDL_Rect){
   return 0;
}
