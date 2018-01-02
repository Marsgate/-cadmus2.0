#include "ports.h"
#include "API.h"

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
    while(digitalRead(SCOOP_LIM_BOT) == HIGH){
      delay(20); //delay to make room for the other tasks to run
    }
    delay(300);
    scoop(0);
  }else{
    scoop(127);
    while(digitalRead(SCOOP_LIM_TOP) == HIGH){
      delay(20); //delay to make room for the other tasks to run
    }
    delay(400);
    scoop(0);
  }
}
