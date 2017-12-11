#include "main.h"

void chainbar(int vel){
  motorSet(CHAINBAR1, vel);
}
void chainbarOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    chainbar(127);
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    chainbar(-127);
  }else{
    chainbar(0);
  }
}
