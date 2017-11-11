#include "main.h"

void right(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE3, vel);
}
void left(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE4, vel);
}

void driveOp(){
  left(joystickGetAnalog(2, 3));
  right(joystickGetAnalog(2, 2));
}
