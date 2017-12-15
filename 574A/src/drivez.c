#include "main.h"

void left1(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE3, vel);
}
void right1(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE4, vel);
}

void drivez(int vel){
  right1(vel);
  left1(vel);
}

void drivezOp(){
  left1(joystickGetAnalog(1, 3));
  right1(joystickGetAnalog(1, 2));
}
