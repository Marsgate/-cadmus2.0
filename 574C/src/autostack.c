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
  if(analogRead(ARMPOT) > AP_STACK){
    arm(0);
  }else{
    arm(vel);
  }
  //lift control
  switch(stackHeight){
    case 0:
      liftPos = LP_LOW;
      break;
    case 1:
      liftPos = LP_LMID;
      break;
    case 2:
    case 3:
      liftPos = LP_HIGH;
      if(analogRead(LIFTPOT) < LP_LMID) arm(0);
      if(analogRead(ARMPOT) > AP_AS) liftPos = LP_LOW;
  }
  liftPID(liftPos); // sets the lift target for PID
}


void retract(){
  if(analogRead(ARMPOT) < AP_BOT){
    arm(-15); //hold arm down
    lift(-127); // lower lift
    if(analogRead(LIFTPOT) < LP_BOT) lift(-25);
  }else{
    if(analogRead(ARMPOT) > AP_MID && stackHeight > 0) lift(127);
    gripSpeed = -127;
    claw(-127);
    if(stacking == false){ //if claw is open
      claw(0);
      arm(-127);
      if(analogRead(ARMPOT) < AP_MID){
        lift(-127); // lower lift
        arm(0); // slow arm descent to prevent slamming
      }
    }else if(analogRead(CLAWPOT) > CP_OPEN) stacking = false; // don't tratract until claw is open
  }
  lcdPrint(uart1, 1, "Stacking: %d", stacking);
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

  //alternate controller
  if(joystickGetDigital(2, 7, JOY_LEFT)){
    stackHeight = 0; // low
  }else if(joystickGetDigital(2, 7, JOY_DOWN)){
    stackHeight = 1; // low mid
  }else if(joystickGetDigital(2, 7, JOY_RIGHT)){
    stackHeight = 2; // high mid
  }else if(joystickGetDigital(2, 7, JOY_UP)){
    stackHeight = 3; // high
  }
}

void autoStack(){
  //set the arm and lift to 0 power
  arm(0);
  lift(0);

  shSelector(); // find out current stack height from second controller

  if(joystickGetDigital(1, 5, JOY_DOWN)){
    stacking = true;
    stack(127); // start the auto stacker if left trigger is pressed
  }else{
    retract(); // retract the lift if no button is pressed
  }
}
