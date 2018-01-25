#include "main.h"

void left(int vel){
  motorSet(DRIVEL1, vel);
  motorSet(DRIVEL2, vel);
}

void right(int vel){
  motorSet(DRIVER1, vel);
  motorSet(DRIVER2, vel);
}

void driveOp(){
  left(joystickGetAnalog(1, 3));
  right(joystickGetAnalog(1, 2));
}
