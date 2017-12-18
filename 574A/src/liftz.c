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
  if (joystickGetDigital(1, 8,JOY_UP)) {

    barz(127);//start of one
    delay(1425);
    barz(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    barz(-90);
    delay(1525);
    barz(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of one
    barz(127);//start of two
    delay(1300);
    barz(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    barz(-90);
    delay(1400);
    barz(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of two
    barz(127);//start of three
    delay(1100);
    barz(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    barz(-90);
    delay(1200);
    barz(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of three

  }
}
