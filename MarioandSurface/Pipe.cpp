//Pipe intstantiation

#include "SDL2/SDL.h"
#include "Pipe.h"
#include "globalVars.h"

Pipe::Pipe(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
//size is special here because it is not the usual 40x40, it's 80x80
  size = blockSize*2;

//determine the height of the pipe
  height = 12 * blockSize - position.y;
  

//since the pipe has special width and height, redefine the width and height
  position.w = size;
  position.h = size;

//pipe sprite
  sprite.x = 614;
  sprite.y = 46;
  sprite.w = 32;
  sprite.h = 31;

//extra pipe sprite
  extraPipeSprite.x = 614;
  extraPipeSprite.y = 81;
  extraPipeSprite.w = 32;
  extraPipeSprite.h = 16;

//extra pipe position
  extraPipePosition.x = position.x;
  extraPipePosition.y = position.y + blockSize;
  extraPipePosition.w = 2 * blockSize;
  extraPipePosition.h = height - blockSize;
}

void Pipe::render(){
  //we still need to keep rendering pipe if it's more than 2 blocks above ground
  if((height - 2 * blockSize) != 0){
    SDL_RenderCopyEx( gRenderer, blockSheet, &extraPipeSprite, &extraPipePosition, 0, NULL, SDL_FLIP_NONE );
  }

  //call the nonmoving class's render function
  NonMoving::render();

}

void Pipe::collision(){}

