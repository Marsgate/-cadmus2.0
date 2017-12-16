#include "main.h"

void antitip(int vel){
  motorSet(ANTITIP, vel);
}
void antitipOp(){
  if(joystickGetDigital(2, 5, JOY_UP)){
    antitip(-127);
  }else if(joystickGetDigital(2, 5, JOY_DOWN)){
    antitip(127);
  }else{
    antitip(0);
  }
}
