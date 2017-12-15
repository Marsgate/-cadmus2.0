#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"
#include "sensorTargets.h"

#define CP 15 // pause to allow the claw to open

int stackHeight = 0; // variable changed by the second controller to control stack height
bool stacking = false; // tracks current autostacker state
int liftPos = LP_BOT;
int clawTimer = 0; //keeps track of how long the claw has been opening

void stack(int vel){
  if(analogRead(ARMPOT) < AP_STACK){
    arm(0);
  }else{
    arm(vel);
  }

  claw(30); //squeeze

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
      liftPos = LP_HIGH;
      arm(80); //slower velocity for highstack
  }
  liftPID(liftPos); // sets the lift target for PID


}


void retract(){

  if(analogRead(ARMPOT) > AP_BOT){
    arm(0); //stop arm

    if(mode == 0){
      if(analogRead(LIFTPOT) < LP_BOT){
        lift(0);
      }else{
        lift(-60);
      }
    }else{
      liftPID(LP_ML);
    }
  }else{
    hold = false;

    if(mode == 1){
      liftPID(LP_HIGH);
    }
    if(stackHeight > 0){
      liftPID(liftPos+200); // hold the lift in place
    }

    if(stacking == false){ //if claw is open
      liftPID(LP_HIGH);
      if(analogRead(ARMPOT) > AP_MID){ // slow retraction after arm midpoint
        arm(0); // cut power prevents slamming
      }else{
        arm(-127);
      }
    }else{

      //pause to allow the claw to open
      claw(-127);
      clawTimer++;
      if(clawTimer >= CP){
        claw(-10);
        clawTimer = 0;
        stacking = false; // finish opening claw
      }
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
