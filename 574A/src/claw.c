#include "main.h"

void claw(int vel){
  motorSet(CLAW, vel);
}

void clawOp(){
  claw(joystickGetAnalog(1, 2));
}
