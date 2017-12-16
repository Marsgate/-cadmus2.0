#include "main.h"

void leftz(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE3, vel);
}
void rightz(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE4, vel);
}

void drivez(int vel){
  rightz(vel);
  leftz(vel);
}

void drivezOp(){
  leftz(joystickGetAnalog(1, 3));
  rightz(joystickGetAnalog(1, 2));
}
