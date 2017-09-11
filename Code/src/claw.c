#include "ports.h"
#include "API.h"

bool hold = false;

void claw(int vel){
  motorSet(CLAW, vel);
}

void clawOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    claw(50);
    hold = true;
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    claw(-50);
    hold = false;
  }else{
    if(hold == true){
      claw(30);
    }else{
      motorStop(CLAW);
    }
  }
}
