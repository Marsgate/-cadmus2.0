#include "API.h"
#include "lift.h"
#include "claw.h"
#include "main.h"
#include "arm.h"
#include "ports.h"

//lift potentiometer stack target constants
#define PT_LOW 700
#define PT_LMID 1500
#define PT_HMID 1850
#define PT_HIGH 2100
#define PT_BOTTOM 350

//chainbar encoder constants
#define ET_HIGH 160
#define ET_MID 100
#define ET_LOW 60

#define controller 1 // defines the number of plugged in controllers

int stackHeight = 0; // variable changed by the second controller to control stack height
bool stacking = false; // tracks current autostacker state

void stack(int vel){
  arm(vel); // start arm moving at the set velocity

  //lift control
  switch(stackHeight){
    case 0:
      liftPID(PT_LOW);
      break;
    case 1:
      liftPID(PT_LMID);
      break;
    case 2:
      liftPID(PT_HMID);
      break;
    case 3:
      liftPID(PT_HIGH);
      arm(80); //slower velocity for highstack
  }

  //slow the arm to prevent damage
  if(encoderGet(armEnc) > ET_HIGH){
    arm(0); // stop arm when stack is complete
  }else if(encoderGet(armEnc) > ET_MID){
    arm(20); // slow arm on descent
  }
}


void retract(){
  liftIntegralReset();

  if(digitalRead(ARM_LIMIT) == LOW){
    arm(0); // stop the arm when it bottoms out
    if(analogRead(LIFTPOT) < PT_BOTTOM){
      lift(0);
    }else{
      lift(-60);
    }
  }else{
    if(encoderGet(armEnc) < ET_LOW){
      arm(-(encoderGet(armEnc)));
    }else{
      arm(-127);
    }

    //open the claw
    claw(-127);
    hold = false;
  }

}

void shSelector(){
  //stack height moves clock wise from the left button
  if(joystickGetDigital(controller, 7, JOY_LEFT)){
    stackHeight = 0; // low
  }else if(joystickGetDigital(controller, 7, JOY_DOWN)){
    stackHeight = 1; // low mid
  }else if(joystickGetDigital(controller, 7, JOY_RIGHT)){
    stackHeight = 2; // high mid
  }else if(joystickGetDigital(controller, 7, JOY_UP)){
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
  }else{
    retract(); // retract the lift if no button is pressed
  }
}
