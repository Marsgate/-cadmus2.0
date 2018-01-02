#include "main.h"

void drive(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE2, vel);
  motorSet(DRIVE3, vel);
  motorSet(DRIVE4, vel);
}

void driveOp(){
  int power = -joystickGetAnalog(1, 3); // vertical axis on right joystick
  int turn  = -joystickGetAnalog(1, 4); // horizontal axis on right joystick
  motorSet(DRIVE1, power + turn); // set left wheels
  motorSet(DRIVE2, power - turn); // set right wheels
  motorSet(DRIVE3, power + turn); // set left wheels
  motorSet(DRIVE4, power - turn); // set right wheels
}
