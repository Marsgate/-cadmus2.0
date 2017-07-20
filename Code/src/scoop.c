#include "ports.h"
#include "API.h"

void scoop(){

  if(joystickGetDigital(1, 5, JOY_UP)){
    motorSet(scoop1, 127);
    motorSet(scoop2, 127);
  }else if(joystickGetDigital(1, 5, JOY_DOWN)){
    motorSet(scoop1, -127);
    motorSet(scoop2, -127);
  }else{
    motorStop(scoop1);
    motorStop(scoop2);
  }

}
