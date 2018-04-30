#include "main.h"

//claw grip definitions and variables
static int gripSpeed = 127;

void claw(int vel){
  motorSet(CLAW, vel);
}

void clawOp(){
  claw(gripSpeed);
  if(buttonGetState(JOY2_6U)){
      gripSpeed = 127;
  }else if(buttonGetState(JOY2_6D)){
      gripSpeed = -127;
  }else if(gripSpeed > 0){
    claw(gripSpeed/6);
  }
}
