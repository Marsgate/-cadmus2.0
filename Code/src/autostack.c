#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "ports.h"

#define ENCTARGET 180
#define POTTARGET 2400 //change to actual


void autoStack(){
  unsigned char button;

  if(joystickGetDigital(1, 7, JOY_DOWN)){
    //first stack
    button = JOY_DOWN;
  }else if(joystickGetDigital(1, 7, JOY_LEFT)){
    //low stack
    button = JOY_LEFT;
  }else if(joystickGetDigital(1, 7, JOY_UP)){
    //high stack
    button = JOY_UP;
  }

  arm(127);
  lift(127);
  while(true){
    if(encoderGet(armEnc) > 0){
      arm(127);
    }else{
      arm(0);
    }

    if(analogRead(LIFTPOT)){
      
    }


  }

}
