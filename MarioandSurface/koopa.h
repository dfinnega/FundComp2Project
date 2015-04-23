#ifndef KOOPA_H
#define KOOPA_H

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
using namespace std;

class Koopa: public Enemy{
	public:
		Koopa( int, int);
		void move(SDL_Rect*);
		void decideFrame();
                int marioCollision(int, SDL_Rect);
         private:
		//int mVelX;
};

#endif
