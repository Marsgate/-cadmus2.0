#include "main.h"

void antitipz(int vel){
  motorSet(ANTITIP, vel);
}
void antitipzOp(){
  if(joystickGetDigital(1, 7, JOY_RIGHT)){
    antitipz(-127);
  }else if(joystickGetDigital(1, 7, JOY_LEFT)){
    antitipz(127);
  }else{
    antitipz(0);
  }
}
