
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

const int LEVEL_WIDTH = 2040;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 500;
const int blockSize = 40;

class LTexture{
  public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path );
        void free(); //deallocates texture
        //renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth();
        int getHeight();
        private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

//quick miscellaneous stuff that I think is needed
LTexture enemyTexture;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

//LTexture functions
LTexture::LTexture(){
   mTexture = NULL;
   mWidth = 0;
   mHeight = 0;
}

LTexture::~LTexture(){
   free();
}

bool LTexture::loadFromFile(std::string path ){
   bool success = false;

  //Get rid of preexisting texture
  free();
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str() );
  if(loadedSurface == NULL){
      printf ("Unable to load image\n");
  }else{
      //Color hey image
      //SDL_SetColorKey(loadedSurface, SDL_True, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

      //create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
      if(newTexture == NULL){
         printf("Unable to create texture from\n");
      }else {
         //get image dimensions
         mWidth = loadedSurface->w;
         mHeight = loadedSurface->h;
      }
      //get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
  }
  return success;
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free(){
  if(mTexture !=NULL){
     SDL_DestroyTexture(mTexture);
     mTexture = NULL;
     mWidth = 0;
     mHeight = 0;
  }
}

void LTexture::render(int x, int y, SDL_Rect* clip){
   //set rendering space and render to screen
   SDL_Rect renderQuad = {x, y, mWidth, mHeight};

   //set CLip rendering dimensions
   if(clip!= NULL){
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
   }

   SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad );
}


int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}


class Enemy{
   public:
        //the dimensions of the enemy
        static const int ENEMY_WIDTH = 40;
        static const int ENEMY_HEIGHT = 40;
   //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;
        //Initializes the variables
        Enemy();
        //moves the enemy
        void move(SDL_Rect*);
        //shows the enemy on the screen
        void render(int, int, SDL_Rect*);
        //accessor functions
        int getPosX();
        int getPosY();
        private:
        //the x and y positions of the enemy
        int mPosX, mPosY;
        //velocity  of the dot
        int mVelX, mVelY;

};
//ass functions
Enemy::Enemy(){
        //initializes the offsets
        mPosX = 0;
        mPosY = 420;
        //initialzes the velocity
        mVelX = 5;
        mVelY = 0;
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
}

void Enemy::render(int camX, int camY, SDL_Rect* clip){
   //show the dot
   enemyTexture.render(mPosX - camX, mPosY - camY, clip);
}

int Enemy::getPosX(){
   return mPosX;
}

int Enemy::getPosY(){
   return mPosY;
}

