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
right(joystickGetAnalog(1,2));
left(joystickGetAnalog(1, 3));
}
