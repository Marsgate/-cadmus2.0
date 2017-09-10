#include "ports.h"
#include "API.h"

bool hold = false;

void grab(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    motorSet(CLAW, 50);
    hold = true;
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    motorSet(CLAW, -50);
    hold = false;
  }else{
    if(hold == true){
      motorSet(CLAW, 30);
    }else{
      motorStop(CLAW);
    }
  }
}
