#include "ports.h"
#include "API.h"

void scoop(int vel){
  motorSet(SCOOP1, vel);
  motorSet(SCOOP2, vel);
}

void scoopOp(){
  if(joystickGetDigital(1, 8, JOY_UP)){
    scoop(127);
  }else if(joystickGetDigital(1, 8, JOY_DOWN)){
    scoop(-70);
  }else{
    scoop(0);
  }
}

void scoopSkills(){
  if(joystickGetDigital(1, 5, JOY_UP)){
    scoop(127);
  }else if(joystickGetDigital(1, 6, JOY_UP)){
    scoop(-70);
  }else{
    scoop(0);
  }
}
