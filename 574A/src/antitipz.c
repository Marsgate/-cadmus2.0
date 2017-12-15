#include "main.h"
void antitipz(int vel){
    motorSet(ANTITIP, vel);
  }

  void antitipzOp(){
    if(joystickGetDigital(1, 5, JOY_UP)){
      antitipz(127);
    }else if(joystickGetDigital(1, 5, JOY_DOWN)){
      antitipz(-127);
    }else{
      antitipz(0);
    }
  }
