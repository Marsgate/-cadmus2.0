#include "main.h"

//claw grip definitions and variables
int gripSpeed = -127;

void claw(int vel){
  motorSet(CLAW, vel);
}

//state changer
void clawGrip(int speed){
  if(buttonGetState(JOY1_6D) == false) speed = speed/6;
  claw(speed);
}

void clawOp(){
  if(buttonIsNewPress(JOY1_6D)){
    if(stacking == true){
      gripSpeed = 127;
    }else{
      gripSpeed = -127;
    }
  }
  clawGrip(gripSpeed);
}
