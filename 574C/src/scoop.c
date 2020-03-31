#include "main.h"
#include "sensorTargets.h"

void scoop(int vel){
  motorSet(SCOOP1, -vel);
  motorSet(SCOOP2, -vel);
}

void scoopOp(){
  if(buttonGetState(JOY1_5U)){
    scoop(127);
  }else if(buttonGetState(JOY1_6U)){
    scoop(-70);
  }else{
    scoop(0);
  }
}

void autoScoop(int target){
  //0 = down, 1 = up
  if(scoopTarget < 2) scoop(0);
  if(target == 0){
    hasPylon = false;
    scoopTarget = 0;
    if(analogRead(SCOOPPOT) > SP_BOT) scoop(-127);
  }else if(target == 1){
    hasPylon = true;
    scoopTarget = 1;
    if(analogRead(SCOOPPOT) < SP_TOP) scoop(127);
  }
}

void manualDrop(){
  hasPylon = false;
  scoopTarget = 2;
  scoop(-127);
  delay(1000);
  scoop(0);
}
