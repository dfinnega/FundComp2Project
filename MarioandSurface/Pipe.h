//this is the Pipe class, used to render Pipes

#include "NonMoving.h"

#ifndef PIPE_H
#define PIPE_H

class Pipe: public NonMoving{
  public:
        Pipe(int, int);//constructor
        void collision();//collision animation

};

#endif
