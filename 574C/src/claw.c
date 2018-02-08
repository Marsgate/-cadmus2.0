#include "main.h"

//claw grip definitions and variables
static int thresh = 30;
static int sp = -1000; // set to low number to trigger a reset
int gripSpeed = 0;

void claw(int vel){
  motorSet(CLAW, vel);
}

//state changer if claw stops moving
void clawGrip(int speed){
  int sv = analogRead(CLAWPOT);

  //reset the threshold if outside of bound
  if(abs(sv-sp) > thresh){
    sp = sv;
  }else{
    speed = speed/6;
  }

  claw(speed);
}

void clawOp(){
  /*
  //two state claw grip
  if(joystickGetDigital(1, 6, JOY_UP)){
    gripSpeed = 127;
    sp = -1000;
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    gripSpeed = -127;
    sp = -1000;
  }
  clawGrip(gripSpeed);
  */
  if(buttonGetState(JOY1_6U)){
    claw(127);
  }else if(buttonGetState(JOY1_6D)){
    claw(-127);
  }else{
    claw(0);
  }
}
