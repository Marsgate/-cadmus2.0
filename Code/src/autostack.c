#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

//lift potentiometer stack target constants
#define LP_LOW 720
#define LP_LMID 1300
#define LP_HMID 1620
#define LP_HIGH 2050
#define LP_ML 600
#define LP_BOT 350

#define AP_BOT 4000
#define AP_MID 1800
#define AP_FRONT 100

#define CP 14 // pause to allow the claw to open

int stackHeight = 0; // variable changed by the second controller to control stack height
bool stacking = false; // tracks current autostacker state
int liftPos = LP_BOT;
int clawTimer = 0; //keeps track of how long the claw has been opening

void stack(int vel){
  arm(vel); // start arm moving at the set velocity
  claw(60); //squeeze

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
    arm(0); // stop the arm when it bottoms out
    if(mode != 1){
      if(analogRead(LIFTPOT) < LP_BOT){
        lift(0);
      }else{
        lift(-60);
      }
    }else{
      liftPID(LP_LMID);
    }
  }else{
    //open the claw
    claw(-127);
    hold = false;

    //if claw is open
    if(stacking == false){
      arm(-127);
    }else{
      clawTimer++;
      if(clawTimer >= CP){
        clawTimer = 0;
        stacking = false;
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
    stack(127); // start the auto stacker if left trigger is pressed
    stacking = true;
  }else{
    retract(); // retract the lift if no button is pressed
  }
}
