#include "main.h"

void pylon(int vel){
  motorSet(PYLON1, vel);
  motorSet(PYLON2, vel);
}



void pylonOp(){
pylon(-joystickGetAnalog(1, 2));
}
