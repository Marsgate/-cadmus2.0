#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGETLOW 630 //change to actual

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

void autoStack(){
  if(joystickGetDigital(1, 5, JOY_DOWN)){
    lowStack();
  }
}
