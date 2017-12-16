#include "main.h"
#include "clawz.h"
#include "claw.h"
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
void autostackzOp(){
  while(1){barz(127);
  delay(550);
  claw(127);
  delay(200);
  barz(0);
  claw(0);
  delay(50);
  barz(-127);
  delay(550);
  claw(-127);
  delay(200);
  barz(0);
  claw(0);
  delay(50);
  if (joystickGetDigital(1, 8, JOY_RIGHT)) {
    break;
    delay(20);

  }
}

}
