#include "main.h"

void chain(int vel){
  motorSet(CHAIN1,vel);
  motorSet(CHAIN2,vel);
}
void chainOp(){
  if(joystickGetDigital(1, 6,JOY_UP)){
    chain(127);
  }else if(joystickGetDigital(1, 6,JOY_DOWN)){
    chain(-127);
  }else {
    chain(0);
  }

}
