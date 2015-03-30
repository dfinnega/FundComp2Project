/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture( "smb_mario_sheet.bmp" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

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

			
SDL_Rect marioSprites[12];
enum {standr,runr1,runr2,runr3,stopr,jumpr,standl,runl1,runl2,runl3,stopl,jumpl};
//clip sprit sheet
marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 17;
marioSprites[standr].h = 18;

marioSprites[runr1].x = 238;
marioSprites[runr1].y = 0;
marioSprites[runr1].w = 17;
marioSprites[runr1].h = 18;

marioSprites[runr3].x = 267;
marioSprites[runr3].y = 0;
marioSprites[runr3].w = 17;
marioSprites[runr3].h = 18;

marioSprites[runr2].x = 298;
marioSprites[runr2].y = 0;
marioSprites[runr2].w = 17;
marioSprites[runr2].h = 18;

marioSprites[jumpr].x = 359;
marioSprites[jumpr].y = 0;
marioSprites[jumpr].w = 17;
marioSprites[jumpr].h = 18;

marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 16;
marioSprites[standr].h = 18;

marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 16;
marioSprites[standr].h = 18;

			SDL_Rect clip;
                        clip.x = 50;
                        clip.y = 200;
                        clip.w = 40;
                        clip.h = 40;
			//While application is running
		    	int i=0;
			float yvel = 0;
			float yaccel = 0;
			float xvel = 7;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0)
				{
					//User requests quit
					if( e.key.keysym.sym == SDLK_ESCAPE )
					{
						quit = true;
					}
					if( e.key.keysym.sym == SDLK_b )
                                        {
                                                printf("JUMP\n");
						yvel = -10;
						yaccel = 1;
                                        }
				}

				//Clear screen
		                SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
                		SDL_RenderClear( gRenderer );
				int sprite;
				if(clip.y <200) sprite = jumpr;
				else sprite = runr1 + i;
				//Render sprite texture to screen
				SDL_RenderCopy( gRenderer, gTexture, &marioSprites[sprite],&clip );
				//Update screen
				SDL_RenderPresent( gRenderer );
				i++;
				if(i>=3) i=0;

				printf("yvel: %f xvel: %f yaccel: %f\n",yvel,xvel,yaccel);
				yvel += yaccel;
				if(clip.y > 200){ yvel =0; yaccel=0; clip.y=200;} 
				clip.y += yvel;
				clip.x += xvel;
				printf("yvel: %f xvel: %f yaccel: %f clip.y: %i\n",yvel,xvel,yaccel,clip.y);
				if( clip.x>=SCREEN_WIDTH ) clip.x=0;
				SDL_Delay(100);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
