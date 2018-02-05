#include "main.h"

void pylon(int vel){
  motorSet(PYLON1, vel);
  motorSet(PYLON2, vel);
}



void pylonOp(){
pylon(-joystickGetAnalog(1, 2));
}
void autobase(int sp){
  double kp = 0.22;
  int sv = analogRead(BASEPOT);
  int error = sp-sv;
  int speed = error*kp;
  pylon(speed);
}
