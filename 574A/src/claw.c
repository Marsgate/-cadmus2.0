#include "main.h"

void claw(int vel){
  motorSet(CLAW, vel);
}

void clawOp(){
  if(joystickGetDigital(2, 6, JOY_UP)){
    claw(127);
  }else if(joystickGetDigital(2,6,JOY_DOWN)){
    claw(-127);
  }else{
    claw(0);
  }
}
