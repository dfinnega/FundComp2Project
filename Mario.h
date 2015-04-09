#include "SDL2/SDL.h"
#include <iostream>
using namespace std;

#ifndef MARIO_H
#define MARIO_H

class Mario {
  public:
    Mario();
    void handleInput();
    void move();
    void render();
    int onGround();
    void deathAnimation();

  private:
    double xpos, ypos;
    double xvel, yvel;
    double xaccel, yacc;
    int running;
    int xdirection;
    int moving;
    int onGround();
    
    SDL_Rect hitBox;

    SDL_Rect spriteClip;	//allows the sprites to be stretched to blockSize
    SDL_Rect marioSprites[7];	//Holds the clips for each of the Mario sprites

    //The following values are static and const, and are the same for every Mario
    //They are declared in Mario.cpp, and the values are obtained from the physics sheet
    static const double 
		minWalkSpeed,	
		maxRunSpeed,
		maxWalkSpeed,
		walkAccel,
		runAccel,
		gravity[3],
		aGravity[3],
		initialYAccel,
		runDecel,
		releaseDecel,
		skidDecel,
		skidTurn,
		airSkidDecel[3];
};

#endif
