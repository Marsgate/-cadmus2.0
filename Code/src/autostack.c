#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGET 2400 //change to actual

int timer = 0;

void lowStack(){
  arm(127);
  lift(127);

  while(true){

    int i = 0;

    if(encoderGet(armEnc) > ENCTARGET){
      arm(0);
      i++;
    }

    if(analogRead(LIFTPOT) > POTTARGET){
      lift(0);
      i++;
    }

    timer += 20;
    if(i == 2 || timer > 3000){break;};
  }

}

void autoStack(){
  if(joystickGetDigital(1, 8, JOY_DOWN)){
    lowStack();
  }
}
