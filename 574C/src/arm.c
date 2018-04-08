#include "main.h"
#include "ports.h"

// motion control for the arm
void arm(int vel){
  motorSet(ARM1, vel);
}

void autoArm(int sp){
  if(sp == 0){
    while(analogRead(ARMPOT) < AP_OUT) arm(-127);
  }else{
    while(analogRead(ARMPOT) > AP_IN) arm(127);
  }
  arm(0);
}

void armOp(){
  if(buttonGetState(JOY2_5U)){
    arm(127);
  }else if(buttonGetState(JOY2_5D)){
    arm(-127);
  }else{
    arm(0);
  }
}
