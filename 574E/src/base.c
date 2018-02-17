#include "main.h"

void base(int vel){
  motorSet(BASE1,vel);
  motorSet(BASE2,vel);
}
void baseOp(){
  if(joystickGetDigital(1, 6,JOY_UP)){
    base(127);
  }else if(joystickGetDigital(1, 6,JOY_DOWN)){
      base(-127);
  }else {
    base(0);
  }

}
void autobase(int sp){
  double kp =0.22;
  int sv=analogRead(BASEPOT);
  int error = sp-sv;
  int speed =error*kp;
  base(speed);
}
