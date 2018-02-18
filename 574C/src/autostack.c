#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"
#include "sensorTargets.h"

int stackHeight = 0; // variable changed by the second controller to control stack height
bool stacking = false; // tracks current autostacker state
int liftPos = LP_BOT;

void stack(int vel){
  arm(vel);
  //lift control
  switch(stackHeight){
    case 0:
      liftPos = LP_LOW;
      break;
    case 1:
      liftPos = LP_LMID;
      break;
    case 2:
      liftPos = LP_HMID;
      break;
    case 3:
      if(analogRead(LIFTPOT) < LP_HMID) arm(0);
      liftPos = LP_HIGH;
  }
  liftPID(liftPos); // sets the lift target for PID

  if(analogRead(ARMPOT) > AP_STACK) arm(0);
  if(analogRead(ARMPOT) > AP_AS) lift(0);
}


void retract(){
  arm(-127);
  lift(-10);
  if(analogRead(ARMPOT) < AP_MID){
    if(analogRead(LIFTPOT) > LP_BOT) lift(-127); // lower lift
    arm(-10);
  }else{
    gripSpeed = -127;
    if(analogRead(CLAWPOT) > CP_OPEN){
      arm(0);
      gripSpeed = -10000;
    }
    if(stackHeight > 0) lift(127);
  }
}

void shSelector(){
  //stack height moves clock wise from the left button
  if(joystickGetDigital(1, 7, JOY_LEFT)){
    stackHeight = 0; // low
  }else if(joystickGetDigital(1, 7, JOY_DOWN)){
    stackHeight = 1; // low mid
  }else if(joystickGetDigital(1, 7, JOY_RIGHT)){
    stackHeight = 2; // high mid
  }else if(joystickGetDigital(1, 7, JOY_UP)){
    stackHeight = 3; // high
  }
}

void autoStack(){
  //set the arm and lift to 0 power
  arm(0);
  lift(0);

  shSelector(); // find out current stack height

  if(buttonGetState(JOY1_5D)){
    stacking = true;
    stack(127); // start the auto stacker if left trigger is pressed
  }else{
    retract(); // retract the lift if no button is pressed
  }
}
