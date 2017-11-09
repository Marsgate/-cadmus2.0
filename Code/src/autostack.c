#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

//lift potentiometer stack target constants
#define PT_LOW 720
#define PT_LMID 1300
#define PT_HMID 1620
#define PT_HIGH 2050
#define PT_BOTTOM 350
#define PT_ML 600

//chainbar encoder constants
#define ET_HIGH 115
#define ET_MID 95
#define ET_LOW 100

#define CP 14 // pause to allow the claw to open

int stackHeight = 0; // variable changed by the second controller to control stack height
bool stacking = false; // tracks current autostacker state
int liftPos = PT_BOTTOM;
int clawTimer = 0; //keeps track of how long the claw has been opening

void stack(int vel){
  arm(vel); // start arm moving at the set velocity
  claw(60); //squeeze

  //lift control
  switch(stackHeight){
    case 0:
      liftPos = PT_LOW;
      break;
    case 1:
      liftPos = PT_LMID;
      break;
    case 2:
      liftPos = PT_HMID;
      break;
    case 3:
      liftPos = PT_HIGH;
      arm(80); //slower velocity for highstack
  }
  liftPID(liftPos); // sets the lift target for PID

  //slow the arm to prevent damage
  if(encoderGet(armEnc) > ET_HIGH){
    arm(0); // stop arm when stack is complete
  }else if(encoderGet(armEnc) > ET_MID){
    arm(20); // slow arm on descent
  }
}


void retract(){
  /*if(liftPos > PT_LOW){
    liftPID(liftPos + 150); // hold the lift in place
  }else{
    liftPID(liftPos - 100); // dont raise for first stack setting
  }*/
  if(digitalRead(ARM_LIMIT) == LOW){
    arm(0); // stop the arm when it bottoms out
    if(mode != 1){
      if(analogRead(LIFTPOT) < PT_BOTTOM){
        lift(0);
      }else{
        lift(-60);
      }
    }else{
      liftPID(PT_LMID);
    }
  }else{
    //open the claw
    claw(-127);
    hold = false;

    //if claw is open
    if(stacking == false){
      if(encoderGet(armEnc) > ET_LOW){
        if(encoderGet(armEnc) < ET_HIGH){
          arm(-60);
          claw(-10);
        }else{
          arm(-127);
        }
      }else{
        arm(0);
      }
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
