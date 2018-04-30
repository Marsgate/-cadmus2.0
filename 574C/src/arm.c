#include "main.h"
#include "ports.h"

static int armSpeed = 127;

// motion control for the arm
void arm(int vel){
  motorSet(ARM1, vel);
}

void autoArm(int sp){
  if(sp == 0){
    arm(-127);
    delay(300);
    arm(0);
  }else{
    arm(127);
    delay(300);
    arm(0);
  }
  arm(0);
}

void armOp(){
  static int armTime = 0;
  arm(armSpeed);
  if(buttonGetState(JOY2_5U)){
    armSpeed = 127;
    armTime = 0;
  }else if(buttonGetState(JOY2_5D)){
    armSpeed = -127;
    armTime = 0;
  }else{
    if(armTime > 140) arm(armSpeed/8);
    armTime += 20;
  }
  lcdPrint(uart1, 1, "arm power %d", motorGet(ARM1));
  lcdPrint(uart1, 2, "arm time %d", armTime);
}
