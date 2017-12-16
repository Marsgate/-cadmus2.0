#include "main.h"

void clawz(int vel){
  motorSet(CLAW, vel);
}

void clawzOp(){
  if(joystickGetDigital(1, 5, JOY_UP)){
    clawz(127);
  }else if(joystickGetDigital(1,5,JOY_DOWN)){
    clawz(-127);
  }else{
    clawz(0);
  }
}
