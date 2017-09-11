#include "ports.h"
#include "API.h"

void scoop(){

  if(joystickGetDigital(1, 8, JOY_DOWN)){
    motorSet(SCOOP1, 127);
    motorSet(SCOOP2, 127);
  }else if(joystickGetDigital(1, 8, JOY_UP)){
    motorSet(SCOOP1, -127);
    motorSet(SCOOP2, -127);
  }else{
    motorStop(SCOOP1);
    motorStop(SCOOP2);
  }
}
