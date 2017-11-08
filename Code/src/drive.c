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

void drivePID(){
  
}


// power curve =============================================
void tankSigLPC(){
  double left;
  double right;
  double lJoy = -joystickGetAnalog(1, 3);
  double rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 8;

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
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
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
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
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
