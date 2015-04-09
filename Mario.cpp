
//declare all of the static variables here
//const static variables
const double Mario::minWalkSpeed = 0.185546875;
const double Mario::maxRunSpeed = 6.40625;
const double Mario::maxWalkSpeed = 3.90625;
const double Mario::walkAccel = 0.092773438;
const double Mario::runAccel = 0.139160156;
const double Mario::gravity[3] = { 1.09375, 0.9375, 1.40625 };
const double Mario::aGravity[3] = { 0.3125, 0.29296875, 0.390625 };
const double Mario::initialYAccel[3] = { 10, 10, 12.5 };
const double Mario::runDecel = 0.25390625;
const double Mario::releaseDecel = 0.126953125;
const double Mario::skidDecel = 0.25390625;
const double Mario::skidTurn = 1.40625;
const double Mario::airSkidDecel[3] = {0.109863281, 0.09765625, 0.063476563};

//The default constructor
Mario::Mario(){
  //start by clipping sprite sheet correctly
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
}

void Mario::move(){

}

void Mario::render(){

}

int Mario::sprite(){

}

void Mario::handleInput(){

}

int Mario::collision(){

}


