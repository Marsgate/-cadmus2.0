#include "main.h"

void pylon(int val){
  digitalWrite(PYLON1, val);
  digitalWrite(PYLON2, val);
}

void pylonOp(){
  if(joystickGetDigital(1, 8, JOY_UP)){
    pylon(HIGH);
  }else if(joystickGetDigital(1, 8, JOY_DOWN)){
    pylon(LOW);
  }
}
