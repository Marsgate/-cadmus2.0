#include "main.h"

void liftz(int vel){
  motorSet(LIFT1, vel);

}

void liftzOp(){
  if(joystickGetDigital(1,8, JOY_UP)){
    liftz(127);
  }else if(joystickGetDigital(1,8, JOY_DOWN)){
    liftz(-127);
  }else{
    liftz(0);
  }
}
void barz(int vel){
  motorSet(LIFT2, vel);
}
void barzOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    barz(127);
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    barz(-127);
  }else{
    barz(0);
  }
}
