#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGETLOW 700
#define POTTARGETMID 1450
#define POTTARGETBOTTOM 350
#define POTTARGETHIGH 1900
#define ENCMID 100

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
  arm(-127);

  if(digitalRead(ARM_LIMIT) == LOW){
    arm(0);
  }else if(encoderGet(armEnc) < ENCMID){
    arm(-20);
    lift(-59);
  }else{
    claw(-127);
    hold = false;
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
