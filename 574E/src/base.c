#include "main.h"

void base(int vel){
  motorSet(BASE1,vel);
  motorSet(BASE2,vel);
}
void baseOp(){
  if(joystickGetDigital(1, 8,JOY_UP)){
    base(127);
  }else if(joystickGetDigital(1, 8,JOY_DOWN)){
      base(-127);
  }else {
    base(0);
  }

}
