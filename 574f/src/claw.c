#include "main.h"

static int hold = false;

void claw(int vel){
  motorSet(CLAW, vel);
}

void clawOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    claw(127);
    hold = true;
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    claw(-127);
    hold = false;
  }else{
    if(hold == true){
      claw(30);
    }else if (hold == false){
      claw(-30);
    }else{
      claw(0);
    }
  }
}
