#include "main.h"

void right(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE4, vel);
}
void left(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE3, vel);
}
void drive(int vel){
  right(vel);
  left(vel);
}

void driveOp(){
  int power;
  int turn;
  power = joystickGetAnalog(1, 3); // vertical axis on right joystick
  turn  = joystickGetAnalog(1, 4); // horizontal axis on right joystick
  left(power + turn); // set left wheels
  right(power - turn); // set right wheels
}
