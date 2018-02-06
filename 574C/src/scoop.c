#include "ports.h"
#include "API.h"
#include "sensorTargets.h"

void scoop(int vel){
  motorSet(SCOOP, -vel);
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

void autoScoop(int target){
  //0 = down, 1 = up
  if(target == 0){
    scoop(-127);
    while(analogRead(SCOOPPOT) > SP_BOT){
      delay(20); //delay to make room for the other tasks to run
    }
    scoop(-127);
    delay(250);
  }else{
    scoop(127);
    while(analogRead(SCOOPPOT) < SP_TOP){
      delay(20); //delay to make room for the other tasks to run
    }
  }
  scoop(0);
}
