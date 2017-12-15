#include "main.h"
void pylonz(int vel){
    motorSet(PYLON1, vel);
    motorSet(PYLON2, vel);
  }

  void pylonzOp(){
    if(joystickGetDigital(1, 6, JOY_UP)){
      pylonz(127);
    }else if(joystickGetDigital(1, 6, JOY_DOWN)){
      pylonz(-127);
    }else{
      pylonz(0);
    }
  }
