#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGETLOW 780
#define POTTARGETMID 1350
#define POTTARGETBOTTOM 350
#define POTTARGETHIGH 1800
#define ENCMID 100

void lowStack(){
  arm(127);
  lift(127);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(20);
  }

  if(analogRead(LIFTPOT) > POTTARGETLOW){
    lift(0);
  }
}

void midStack(){
  arm(127);
  lift(127);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(60);
  }

  if(analogRead(LIFTPOT) > POTTARGETMID){
    lift(0);
  }
}

void highStack(){
  arm(127);
  lift(127);

  if(encoderGet(armEnc) > ENCTARGET){
    arm(0);
  }else if(encoderGet(armEnc) > ENCMID){
    arm(60);
  }

  if(analogRead(LIFTPOT) > POTTARGETHIGH){
    lift(0);
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
