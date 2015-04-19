/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "init.h"
#include "Mario.h"
#include "NonMoving.h"
#include "Brick.h"
#include "Pipe.h"
#include "Question.h"
#include "Ground.h"
#include "Stair.h"
#include "globalVars.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 520; 
const int blockSize = 40; 
 
//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 
 
//The window renderer 
SDL_Renderer* gRenderer = NULL; 
 
//Declare new textures 
SDL_Texture* marioSheet = NULL; 
SDL_Texture* blockSheet = NULL; 

//=========================================================================
//Begin main program
int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() ) {
	printf( "Failed to initialize!\n" );
	return 1;
  }
  //Load media
  if( !loadMedia() ) {
	printf( "Failed to load media!\n" );
	return 2;
  }
  //Main loop flag
  bool quit = false;

  //Event handler, only accepts the esc key to quit program
  //all other events are processed by Mario's class
  SDL_Event e;

  //loop counter, to determine timing and such
  int i=0;

  //declare the different classes
  Brick brick2(6,9);
  Brick brick1(4,9);
  Pipe pipe1(12,11);
  Question quest(5,9);
  Mario mario;

  //create list of nonmoving elements
  vector<NonMoving*> nonmoving;
  nonmoving.push_back(&brick1);
  nonmoving.push_back(&brick2);
  nonmoving.push_back(&pipe1);
  nonmoving.push_back(&quest);
  for(int k=0;k<16;k++){
	nonmoving.push_back(new Ground(k+1, 13));
  }
  for(int k=0; k<4; k++){
	nonmoving.push_back(new Ground(k+1, k+1));
  }
	


  //Start the game loop
  while( !quit ){
	//Handle events on queue (quit or no quit)
	while( SDL_PollEvent( &e ) != 0) {
		if(e.key.keysym.sym == SDLK_ESCAPE) { //User requests quit
			quit = true;
			break;
		}
	}

//==================================================================================================
  //handle Mario's input from the 
  mario.handleInput(i);

//===============================================================================================

//Rendering function
  //Clear screen
  SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
  SDL_RenderClear( gRenderer );

  mario.render();
  for(int j=0; j<nonmoving.size(); j++){
	nonmoving[j]->render();
  }

  //Update screen
  SDL_RenderPresent( gRenderer );
//===============================================================================================

  //Move Mario function 
  //This next block updates Mario's position
  i++;//increment the loopcount
  mario.move(i);  

  if(i>100) nonmoving[4]->collision();
  //delays to set proper framerate
  SDL_Delay(16);
  }

//Free resources and close SDL
close();

return 0;
}
