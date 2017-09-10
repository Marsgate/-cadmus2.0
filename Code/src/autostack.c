#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGETLOW 700
#define POTTARGETHIGH 2100
#define POTTARGETBOTTOM 350

int timer = 0;

void lowStack(){
  arm(127);
  lift(127);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }

  if(analogRead(LIFTPOT) > POTTARGETLOW){
    lift(0);
  }
}

void highStack(){
  arm(127);
  lift(127);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }

  if(analogRead(LIFTPOT) > POTTARGETHIGH){
    lift(0);
  }
}

void retract(){
  arm(-127);
  lift(-127);

  if(digitalRead(ARM_LIMIT) == LOW){
    arm(0);
  }

  if(analogRead(LIFTPOT) > POTTARGETBOTTOM){
    lift(0);
  }
}


void autoStack(){
  if(joystickGetDigital(1, 5, JOY_DOWN)){
    lowStack();
  }else if(joystickGetDigital(1, 5, JOY_UP)){
    highStack();
  }else{
    //retract();
  }
}
