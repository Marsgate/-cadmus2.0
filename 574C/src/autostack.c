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

void stack(){
  arm(127);
  //lift control
  switch(stackHeight){
    case 0:
      liftPos = LP_LOW;
      if(analogRead(ARMPOT) > AP_AS) lift(0);
      break;
    case 1:
      liftPos = LP_LMID;
      break;
    case 2:
      liftPos = LP_HMID;
      armPID(AP_AUTO+50);
      if(analogRead(LIFTPOT) < LP_LMID) arm(0);
      break;
    case 3:
      liftPos = LP_HIGH;
      armPID(AP_AUTO-50);
      if(analogRead(LIFTPOT) < LP_LMID) arm(0);
  }
  liftPID(liftPos); // sets the lift target for PID
  if(analogRead(ARMPOT) > AP_STACK && stackHeight < 2) arm(25);
}


void retract(){
  if(stacking == false) arm(-127);
  lift(-10);
  if(analogRead(ARMPOT) < AP_MID){
    if(analogRead(LIFTPOT) > LP_BOT) lift(-127); // lower lift
    arm(-30);
  }else{
    gripSpeed = -127;
    if(analogRead(CLAWPOT) > CP_OPEN){
      arm(0);
      gripSpeed = -10000;
    }
    if(stackHeight == 1){
      if(analogRead(LIFTPOT) > liftPos + 200) stacking = false; // raise lift to preven ripping cones off of the stack
      lift(127);
    }else{
      stacking = false;
    }
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
    stack(); // start the auto stacker if left trigger is pressed
  }else{
    retract(); // retract the lift if no button is pressed
  }
}
