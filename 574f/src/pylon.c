#include "main.h"

void pylon(int vel){
  motorSet(PYLON, vel);
}

void pylonOp(){
  if(joystickGetDigital(1, 8, JOY_UP)){
    pylon(127);
  }else if(joystickGetDigital(1, 8, JOY_DOWN)){
    pylon(-127);
  }else{
    pylon(0);
  }
}