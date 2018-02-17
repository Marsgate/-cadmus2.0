#include "main.h"

void right(int vel){

  motorSet(DRIVE2, vel);
  motorSet(DRIVE3, vel);
}
void left(int vel){
  motorSet(DRIVE1, vel);
  motorSet(DRIVE4, vel);


}
void drive(int vel){
  right(vel);
  left(vel);
}

void ultraDrive(){
  int target = 5;
  drive(127);
  while(ultrasonicGet(sonar) > target && ultrasonicGet(sonar) != ULTRA_BAD_RESPONSE);
  drive(0);
}

void driveForward(int target){
  drive(127);
  while((encoderGet(encoder_l) + encoderGet(encoder_r))/2 < target);
  drive(0);
}
void driveBackward(int target){
  drive(-127);
  while((encoderGet(encoder_l) + encoderGet(encoder_r))/2 > target);
  drive(0);
}

void driveOp(){
  int deadzone = 15;
  int rJoy = joystickGetAnalog(1, 2);
  int lJoy = joystickGetAnalog(1, 3);
  drive(0);
  if(abs(rJoy) > deadzone) right(rJoy);
  if(abs(lJoy) > deadzone) left(lJoy);
}

void autodrive(int distance){
  int enc;
  if(distance > 0){
  do{
  enc = (encoderGet(encoder_l)+encoderGet(encoder_r))/2;
  drive(127);
  }while(enc < distance);
  drive(0);
  }else{
  do{
  enc = (encoderGet(encoder_l)+encoderGet(encoder_r))/2;
  drive(-127);
  }while(enc > distance);
  drive(0);
  }
}
void e_reset(){
encoderReset(encoder_l);
encoderReset(encoder_r);
}
