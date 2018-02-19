#include "main.h"

void pylon(int vel){
  motorSet(PYLON1, vel);
  motorSet(PYLON2, vel);
}



void pylonOp(){
pylon(-joystickGetAnalog(1, 2));
}
void pylon2Op(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    pylon(-127);
  }else if(joystickGetDigital(1,6,JOY_DOWN)){
    pylon(127);
  }else{
    pylon(0);
  }
}
void autobase(int sp){
  double kp = 0.22;
  int sv = analogRead(BASEPOT);
  int error = sp-sv;
  int speed = error*kp;
  pylon(-speed);
}
