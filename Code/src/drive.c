#include "main.h"
#include "ports.h"
#include "math.h"

//generic drive functions =============================================
void leftD(int vel){
  motorSet(DRIVEL1, vel);
}
void rightD(int vel){
  motorSet(DRIVER2, vel);
  motorSet(DRIVER1, vel);
}
void drive(int vel){
  motorSet(DRIVEL1, vel);
  motorSet(DRIVER2, vel);
  motorSet(DRIVER1, vel);
}

// power curves =============================================
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

  leftD(left);
  rightD(right);
}

void tankSigLPC(){
  double left;
  double right;
  double lJoy = -joystickGetAnalog(1, 3);
  double rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 5;

  if(abs(lJoy) > deadzone){
    left = log(256/(lJoy+128)-1)/(-.025);
  }else{
    left = 0;
  }
  if(abs(rJoy) > deadzone){
    right = log(256/(rJoy+128)-1)/(-.025);
  }else{
    right = 0;
  }

  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}


// autonomous drive functions =============================================


// forward and backward
void autoDrive(int distance){
  int encAvg = 0;
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  if(distance > encAvg){
    while(distance > encAvg){
      encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
      drive(127);
      printf("EA: %d distance to go:%d\n ", encAvg, (abs(distance) - abs(encAvg)));
      delay(20);
    }
  }else{
    while(distance < encAvg){
      encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
      drive(-127);
      delay(20);
    }
  }
  drive(0);
}

//turning
void autoTurn(int distance, int speed){
  int encAvg = 0;
  int deadzone = 3;
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  while(distance > encAvg + deadzone || distance < encAvg - deadzone){
    encAvg = (-encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
    if(distance > encAvg){
      leftD(speed);
      rightD(-speed);
      printf("EA: %d distance to go:%d\n ", encAvg, (abs(distance) - abs(encAvg)));
      delay(20);
    }
    if(distance < encAvg){
      leftD(-speed);
      rightD(speed);
      delay(20);
    }
  }
}
