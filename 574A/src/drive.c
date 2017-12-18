#include "main.h"

static int mode = 0;

void left1(int vel){
  motorSet(DRIVE2, vel);
  motorSet(DRIVE3,vel);

}
void right1(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE4, vel);
}

void drive1(int vel){
  left1(vel);
  right1(vel);
}
void right0(int vel){
  motorSet(DRIVE2, vel);

  motorSet(DRIVE3,vel);

}
void left0(int vel){
motorSet(DRIVE1, vel);

  motorSet(DRIVE4, vel);
}

void drive0(int vel){
  left0(vel);
  right0(vel);
}
void driveOp(){
  //drive mode selector
  if(joystickGetDigital(2, 8, JOY_UP)){
    mode = 0;
  }else if(joystickGetDigital(2, 8, JOY_DOWN)){
    mode = 1;
  }

  switch(mode){
    case 0:
      left0(joystickGetAnalog(2, 3));
      right0(joystickGetAnalog(2, 2));
      break;
    case 1:
      left1(-joystickGetAnalog(2, 3));
      right1(-joystickGetAnalog(2, 2));
      break;
  }
}
