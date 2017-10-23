#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGETLOW 810
#define POTTARGETMID 1450
#define POTTARGETBOTTOM 350
#define POTTARGETHIGH 1850
#define ENCMID 100

void lowStack(){
  arm(127);
  liftPID(POTTARGETLOW);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(20);
  }

}

void midStack(){
  arm(127);
  liftPID(POTTARGETMID);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(60);
  }
}

void highStack(){
  arm(127);
  liftPID(POTTARGETHIGH);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(60);
  }

}


void retract(){

  if(digitalRead(ARM_LIMIT) == LOW){
    arm(0);
  }else{
    arm(-127);
    claw(-127);
    hold = false;
  }

  if(digitalRead(ARM_LIMIT) == LOW && analogRead(LIFTPOT) > POTTARGETBOTTOM){
    lift(-60);
  }
  if(analogRead(LIFTPOT) < POTTARGETBOTTOM){
    lift(0);
  }
}


void autoStack(){
  arm(0);
  lift(0);
  if(joystickGetDigital(1, 5, JOY_DOWN) && joystickGetDigital(1, 5, JOY_UP)){
    highStack();
  }else if(joystickGetDigital(1, 5, JOY_DOWN)){
    lowStack();
  }else if(joystickGetDigital(1, 5, JOY_UP)){
    midStack();
  }else{
    retract();
  }
}
