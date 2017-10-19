#include "API.h"
#include "ports.h"
#include "math.h"

void arcade(){
  int power;
  int turn;
  power = -joystickGetAnalog(1, 3); // vertical axis on left joystick
  turn  = joystickGetAnalog(1, 4); // horizontal axis on left joystick
  motorSet(DRIVEL1, power - turn); // set left wheels
  motorSet(DRIVER1, power + turn); // set right wheels
  motorSet(DRIVER2, power + turn); // set right
}

void tankHPC(){
  int left;
  int right;
  int lJoy;
  int rJoy;
  lJoy = -joystickGetAnalog(1, 3);
  rJoy = -joystickGetAnalog(1, 2);
  left = (-1 * (lJoy*lJoy)/127)+(2*lJoy);
  right = (-1 * (rJoy*rJoy)/127)+(2*rJoy);
  if(lJoy < 0){
    lJoy = abs(lJoy);
    left = (-1 * (lJoy*lJoy)/127)+(2*lJoy);
    left = -left;
  }
  if(rJoy < 0){
    rJoy = abs(rJoy);
    right = (-1 * (rJoy*rJoy)/127)+(2*rJoy);
    right = -right;
  }
  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}

void tankLPC(){
  //get Joystick values
  int left;
  int right;
  int lJoy = -joystickGetAnalog(1, 3);
  int rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 5;
  int boost = 19;

  if(lJoy > deadzone){
    left = pow(127-boost, lJoy/127)+boost;
  }else if(lJoy < deadzone){
    left = -(pow(127-boost, lJoy/127)+boost);
  }else{
    left = 0;
  }

  if(lJoy > deadzone){
    right = pow(127-boost, rJoy/127)+boost;
  }else if(lJoy < deadzone){
    rJoy = abs(rJoy);
    right = -(pow(127-boost, rJoy/127)+boost);
  }else{
    right = 0;
  }

  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}

/*
void tankSigHPC(){
  int left;
  int right;
  int lJoy = -joystickGetAnalog(1, 3);
  int rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 5;

  if(abs(lJoy) > deadzone){
    left = (127/(1 + pow(2.72,-.05*lJoy)))*2-127;
  }else{
    left = 0;
  }
  if(abs(rJoy) > deadzone){
    right = (127/(1 + pow(2.72,-.05*rJoy)))*2-127;
  }else{
    right = 0;
  }

  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}

void tankSigLPC(){
  int left;
  int right;
  int lJoy = -joystickGetAnalog(1, 3);
  int rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 5;

  if(abs(lJoy) > deadzone){
    left = log((256/lJoy+128)-1)/-0.02;
  }else{
    left = 0;
  }
  if(abs(rJoy) > deadzone){
    right = log((256/rJoy+128)-1)/-0.02;
  }else{
    right = 0;
  }

  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}
*/
