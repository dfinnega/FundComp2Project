//Pipe intstantiation

#include "SDL2/SDL.h"
#include "Pipe.h"
#include "globalVars.h"

Pipe::Pipe(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
//size is special here because it is not the usual 40x40, it's 80x80
  size = blockSize*2;

//since the pipe has special width and height, redefine the width and height
  position.w = size;
  position.h = size;

//pipe sprite
  sprite.x = 614;
  sprite.y = 46;
  sprite.w = 32;
  sprite.h = 32;
}

void Pipe::collision(){}

