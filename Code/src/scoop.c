#include "ports.h"
#include "API.h"

static int vel = 0;

void scoop(int vel){
  motorSet(SCOOP1, vel);
  motorSet(SCOOP2, vel);
}

void scoopOp(){

  //get the speed for the scoop
  if(joystickGetDigital(2, 6, JOY_UP)){
    vel = 127;
  }else  if(joystickGetDigital(2, 6, JOY_DOWN)){
    vel = -70;
  }

  if(joystickGetDigital(1, 5, JOY_UP)){
    scoop(vel);
  }else{
    scoop(0);
  }
}
