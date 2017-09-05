#include "API.h"
#include "ports.h"

void lift(){
  if (joystickGetDigital(1,5,JOY_UP)){
    motorSet(LIFT1, 127);
    motorSet(LIFT2, 127);
  }else if (joystickGetDigital(1, 5, JOY_DOWN)){
    motorSet(LIFT1, -127);
    motorSet(LIFT2, -127);
  }else{
    motorStop(LIFT1);
    motorStop(LIFT2);
  }
}
