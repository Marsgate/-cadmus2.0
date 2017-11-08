#include "ports.h"
#include "API.h"

static int vel = 0;

void scoop(int vel){
  motorSet(SCOOP1, vel);
  motorSet(SCOOP2, vel);
}

void scoopOp(){

  if(joystickGetDigital(1, 8, JOY_UP)){
    scoop(127);
  }else if(joystickGetDigital(1, 8, JOY_DOWN)){
    scoop(-70);
  }else{
    scoop(0);
  }
}
