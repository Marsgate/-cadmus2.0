#include "main.h"

void pylon(int val){
  motorSet(PYLON, val);

}

void pylonOp(){
  if(joystickGetDigital(1, 8, JOY_UP)){
    pylon(HIGH);
  }else if(joystickGetDigital(1, 8, JOY_DOWN)){
    pylon(LOW);
  }
}
