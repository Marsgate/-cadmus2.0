#include "main.h"
#include "ports.h"
#include "math.h"

static int integral = 0;
static int prevErr = 0;

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

void drivePID(int vel){
  int el = abs(encoderGet(driveEncLeft));
  int er = abs(encoderGet(driveEncRight));

  //constants
  double kp = 1.3;
  double ki = 0.02;
  double kd = 2;

  // define local variables
  int speed; // speed
  int derivative; // derivative

  int error;

  //full speed to the slower moter
  if(el > er){
    rightD(vel);
    error = el - er;
  }else{
    leftD(vel);
    error = er - el;
  }

  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = 127 - abs(error*kp + integral*ki + derivative*kd); // add the values to get the motor speed

  if(el < er){
    leftD(speed);
  }else{
    rightD(speed);
  }
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
  int encAvg = 0;
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  if(distance > encAvg){
    while(distance > encAvg){
      encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
      drivePID(127);
      printf("EA: %d distance to go:%d\n ", encAvg, (abs(distance) - abs(encAvg)));
      delay(20);
    }
  }else{
    while(distance < encAvg){
      encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
      drivePID(-127);
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
