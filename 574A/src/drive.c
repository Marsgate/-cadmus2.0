#include "main.h"

void right(int vel){
  motorSet(DRIVE1, vel);
}
void left(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE4, vel);
}

void drive(int vel){
  right(vel);
  left(vel);
}

void driveOp(){
  left(joystickGetAnalog(2, 3));
  right(joystickGetAnalog(2, 2));
}
