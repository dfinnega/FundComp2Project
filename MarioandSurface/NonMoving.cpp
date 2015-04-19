//This is the interface for the nonmoving class
#include "globalVars.h"
#include "NonMoving.h"
#include <iostream>
using namespace std;

NonMoving::NonMoving(int xgrid, int ygrid){
  position.x = (xgrid-1) * blockSize;
  position.y = (ygrid-1) * blockSize;
//set the position's width and height
  position.w = blockSize;
  position.h = blockSize;
}

void NonMoving::render(){
  SDL_RenderCopyEx( gRenderer, blockSheet, &sprite, &position, 0, NULL, SDL_FLIP_NONE );
}
