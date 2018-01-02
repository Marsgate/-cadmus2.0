#include "main.h"

void arm(int vel){
  motorSet(ARM, vel);
}

void armOp(){
  arm(joystickGetAnalog(1, 2));
}
