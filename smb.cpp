/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "init.h"
#include "globalVars.h"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 520; 
const int blockSize = 40; 
 
//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 
 
//The window renderer 
SDL_Renderer* gRenderer = NULL; 
 
//Current displayed texture 
SDL_Texture* gTexture = NULL; 

//=========================================================================
//Begin main program
int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			
SDL_Rect marioSprites[7];
enum {standr,runr1,runr2,runr3,skidr,jumpr,death};
//clip sprit sheet
marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 17;
marioSprites[standr].h = 18;

marioSprites[runr1].x = 238;
marioSprites[runr1].y = 0;
marioSprites[runr1].w = 17;
marioSprites[runr1].h = 18;

marioSprites[runr2].x = 298;
marioSprites[runr2].y = 0;
marioSprites[runr2].w = 17;
marioSprites[runr2].h = 18;

marioSprites[runr3].x = 267;
marioSprites[runr3].y = 0;
marioSprites[runr3].w = 17;
marioSprites[runr3].h = 18;

marioSprites[skidr].x = 330;
marioSprites[skidr].y = 0;
marioSprites[skidr].w = 16;
marioSprites[skidr].h = 17;

marioSprites[jumpr].x = 359;
marioSprites[jumpr].y = 0;
marioSprites[jumpr].w = 17;
marioSprites[jumpr].h = 18;

			SDL_Rect clip;
                        clip.x = 50;
                        clip.y = 200;
                        clip.w = 40;
                        clip.h = 40;
			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			//While application is running
			enum{left, right};
		    	int i=0;
			int j=0;
			int running = 0;
			int skidding = 0;
			double xpos = 50;
			double ypos = 200;
			double yvel = 0;
			double xvel = 0;
			int xdirection = right;
			double xaccel = 0;
			double xmaxSpeed = 0;
			double xinitialJumpVel = 0;//set when Mario jumps, store his jump velocity
			
			//const static variables
			const double minWalkSpeed = 0.185546875;
			const double maxRunSpeed = 6.40625;
			const double maxWalkSpeed = 3.90625;
			const double walkAccel = 0.092773438;
			const double runAccel = 0.139160156;
			const double gravity[3] = { 1.09375, 0.9375, 1.40625 };
			const double aGravity[3] = { 0.3125, 0.29296875, 0.390625 };
			const double initialYAccel[3] = { 10, 10, 12.5 };
			const double runDecel = 0.25390625;
			const double releaseDecel = 0.126953125;
			const double skidDecel = 0.25390625;
			const double skidTurn = 1.40625;
			const double airSkidDecel[3] = {0.109863281, 0.09765625, 0.063476563};
			
			//these are used for running and slowing to a walk
			//Mario keeps running for 10 frames after a button is released
 			int stoppedRunningAt=0,framesPast=0;
			
			//This is used to make sure Mario only jumps once
			int alreadyJumped = 0;
			
			int onGround = 1;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0)
				{
				  switch(e.key.keysym.sym){
					//User requests quit
					case SDLK_ESCAPE:
						quit = true;
						break;
				  }
				}

//==================================================================================================
//Start of event handling function
//This function processes all input for Mario, and updates the velocity values accordingly
//Does not move Mario's position
/* Values this funcation affects:
 * running
 * skidding
 * 

*/

const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
//This block is for the jump key (currently S, but that could change easily)
  //decide which gravity and initial acceleration to use (depends on Mario's speed)
  int gravIndex;
  if(xvel < 2.5) gravIndex=0; 
  else if(xvel >=2.5 && xvel <=5.780639648) gravIndex=1;
  else gravIndex=2;
if( currentKeyStates[ SDL_SCANCODE_S ] ){
  //This means Mario is jumping
  //now update his velocity accordingly
  if(onGround && alreadyJumped == 0 ){
    alreadyJumped = 1;
    xinitialJumpVel = xvel;
    yvel -= initialYAccel[gravIndex];
  } else {
    yvel += aGravity[gravIndex];
  } 
} else { //jump button is not being pressed
  if(onGround){//if Mario is on the ground, yvel = 0
    yvel = 0;
    //only when Mario makes it to the ground is he allowed to jump again
    alreadyJumped = 0;
  } else { //else, fall at normal speed
    yvel += gravity[gravIndex];
  } 
}  

//This block sets the running flag to 1 or 0
//The running flag will be used for the left and right motion
//Mario's horizontal physics change if he is in the air vs. on ground
//if Mario is not on the ground, then the sprint button doesn't matter, only current speed does
if(!onGround){
  if(xvel < maxWalkSpeed){
    xaccel = walkAccel;
  } else { 
    xaccel = runAccel;
  }
//if he's on the ground, check the sprint button
} else if( currentKeyStates[ SDL_SCANCODE_A ] ){
  running = 1;
  xmaxSpeed = maxRunSpeed;
  xaccel = runAccel;
} else if(running == 1 ){ //Mario keeps running for 10 frames, then slows immediately to a walk
  //check if stoppedRunningAt has been set, if it hasn't, set it
  if(!stoppedRunningAt){
    stoppedRunningAt = i;
  }
  framesPast = i - stoppedRunningAt;
  if(framesPast >= 10){//if frames past greater than 10, stop running (decel starts next loop)
    running = 0;
  } 
} else { //Mario is not running, just walking
  //framesPast = 0;//make sure if he was running, this variable is reset
  stoppedRunningAt = 0;
  running = 0;
  //When the run button is released, Mario only changes his speed when he is on the ground
  if(onGround){
    xmaxSpeed = maxWalkSpeed;
    xaccel = walkAccel;
  }
}

//This next block is for the right arrow key
if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
  if(onGround){ xdirection = right; }//only change direction when on the ground
  //if he is moving slower than max, add the acceleration
  if(xvel < xmaxSpeed){
    if(xvel < 0){ //he's moving left, initiate skid
      skidding = 1;
      if(!onGround){//Mario is in the air, initiate arial physics for skidding
	if(xvel > maxWalkSpeed){
	   xvel += airSkidDecel[0];
	} else {
	  if(xinitialJumpVel >= 2.5){
		xvel += airSkidDecel[0];
	  } else {
		xvel += airSkidDecel[0];
	  }
	}
      }
      if(xvel > -1*skidTurn){ // if x is less than the turnaround speed, set xvel to 0
	xvel = minWalkSpeed;
      } else if(onGround) { // else slow him down
	xvel += skidDecel;
      }
    } else if(xvel > 0 && xvel < minWalkSpeed){//This is just moving very slowly right
	skidding = 0;
	xvel = minWalkSpeed;
    } else {
	skidding = 0;
	xvel += xaccel;
    }
  }
  //make sure the speed is not greater than the max run speed
  if(xvel > xmaxSpeed){
    xvel = xmaxSpeed;
  }
} else { //This means the right key is not being pressed
  //only decelerate when Mario is on the ground
  if(xvel >= minWalkSpeed && onGround){
    if(skidding){ //if he was skidding and button is released, he cintinues to slow at skid pace
	xvel -= skidDecel;
    } else { // else he decelerates at normal pace
    	xvel -= releaseDecel;
    }
  } else if(xvel < minWalkSpeed && xvel > 0 && onGround){
    //the min 
    xvel = 0;
  }
}

//This next block is for the left arrow key
if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){
  if(onGround){ xdirection = left; }//only change direction when on the ground
  //if he is moving slower than max, add the acceleration
  if(xvel > -1*xmaxSpeed){
    if(xvel > 0){ //he's moving right, initiate skid
      skidding = 1;
      if(!onGround){//Mario is in the air, initiate arial physics for skidding
        if(xvel < -1*maxWalkSpeed){
           xvel -= airSkidDecel[0];
        } else {
          if(xinitialJumpVel <= -2.5){
                xvel -= airSkidDecel[0];
          } else {
                xvel -= airSkidDecel[0];
          }
        }
      }
      if(xvel < skidTurn){ // if x is less than the turnaround speed, set xvel to 0
        xvel = -1*minWalkSpeed;
      } else if(onGround){ // else slow him down
        xvel -= skidDecel;
      }
    } else if(xvel < 0 && xvel > -1*minWalkSpeed){//This is just moving very slowly right
	skidding = 0;
        xvel = -1*minWalkSpeed;
    } else {
	skidding = 0;
        xvel -= xaccel;
    }
  }
  //make sure the speed is not less than the negative max run speed
  if(xvel < -1*xmaxSpeed){
    xvel = -1*xmaxSpeed;
  }
} else { //This means the left key is not being pressed
  //only decelerate when Mario is on the ground
  if(xvel <= -1*minWalkSpeed && onGround){
    if(skidding){ //if he was skidding and button is released, he cintinues to slow at skid pace
	xvel += skidDecel;
    } else { // else he decelerates at normal pace
    	xvel += releaseDecel;
    }
  } else if(xvel > -1*minWalkSpeed && xvel < 0 && onGround){
    //the min 
    xvel = 0;
  }
}

//if both left and right are held, go nowhere
if( currentKeyStates[ SDL_SCANCODE_LEFT ] && currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
  if(xvel < -1*minWalkSpeed){//going left
    skidding = 0;
    if(onGround) xdirection = right;
    xvel += releaseDecel;
  } else if(xvel > minWalkSpeed){//going right
    skidding = 0;
    if(onGround) xdirection = left;
    xvel -= releaseDecel;
  } else {
    if(onGround) xdirection = right;
    xvel = 0;
  }
}

//==================================================================================================

//sprite function
//decide what clip to render
int sprite;
//first determine the x direction, default is the direction they were facing
if(xdirection == left) { flipType = SDL_FLIP_HORIZONTAL; }
else if(xdirection == right) { flipType = SDL_FLIP_NONE; }

//now decide the type of sprite to render
if(clip.y < 200) sprite = jumpr;//off the ground
else if(xvel==0) {sprite = standr; j=0; }
else if((xvel > 0 && xdirection == left) || (xvel < 0 && xdirection == right)) {
  sprite = skidr;
} else sprite = runr1 + j;
//===============================================================================================

//Rendering function
  //Clear screen
  SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
  SDL_RenderClear( gRenderer );

  //Render sprite texture to screen
  SDL_RenderCopyEx( gRenderer, gTexture, &marioSprites[sprite],&clip,0,NULL,flipType );
  //render horizontal grid to screen
  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
  for(int gridheight=1; gridheight<=SCREEN_HEIGHT/blockSize; gridheight ++){
    SDL_RenderDrawLine( gRenderer, 0, gridheight*blockSize, SCREEN_WIDTH, gridheight*blockSize );
  }

  //Update screen
  SDL_RenderPresent( gRenderer );
//===============================================================================================

//Move Mario function 
  //This next block updates Mario's position
  i++;
  if(i%3 == 0 && running) j++;
  else if(i%5 == 0 && !running) j++;//walking Mario's sprites transition at a rate of 3/5 * running Mario's sprites
  if(j>=3) j=0;
  
  //update y position and check if Mario is on the ground	
  ypos += yvel;
  if(ypos >= 200) { ypos = 200; onGround = 1; }
  else onGround = 0;

  //Update the x position
  xpos += xvel;
  //if Mario is off the screen, rotate to other side of screen
  if(xpos > SCREEN_WIDTH) xpos = 0;//if x is off right side of screen, move to left side of screen
  else if(xpos < -clip.w) xpos = SCREEN_WIDTH;//if x is off left, push to right
	
  // This renders Mario's bottom left at the ypos (for better control of where Mario is)
  clip.y = ypos;// - clip.h; 
  clip.x = xpos;

  //this next line prints Mario's current values
  //printf("yvel: %f xvel: %f clip.y: %i clip.x:%i running:%i onGround:%i\n",yvel,xvel,clip.y,clip.x,running,onGround);
  
  //delays to set proper framerate
  SDL_Delay(16);
  }
  }
}

//Free resources and close SDL
close();

return 0;
}
