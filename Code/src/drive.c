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
  motorSet(DRIVER2, vel-5);
  motorSet(DRIVER1, vel-5);
}


//PID functions =============================================
void drivePID(int sp){
  static int integral = 0;
  static int prevErr = 0;

  double kp = 1;
  double ki = 0;
  double kd = 3;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  drive(speed);
}

void turnPID(int sp){
  static int integral = 0;
  static int prevErr = 0;

  double kp = 2.5;
  double ki = 0.04;
  double kd = 5;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = gyroGet(gyro);
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  if(abs(error) > 10){integral = 0;} // only modify integral if close to target

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed
  leftD(speed);
  rightD(-speed);
}

// power curve =============================================
void tankSigLPC(){
  double left;
  double right;
  double lJoy = -joystickGetAnalog(1, 3);
  double rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 8;

  if(mode == 4){
    lJoy = -lJoy;
    rJoy = -rJoy;
  }

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
  int deadzone = 5;
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  while(distance > encAvg + deadzone || distance < encAvg - deadzone){
    encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
    drivePID(distance);
    delay(20);
  }
  drive(0);
}

//turning
void autoTurn(int distance){
  int gy = gyroGet(gyro);
  int deadzone = 3;
  gyroReset(gyro);
  while(distance > gy + deadzone || distance < gy - deadzone){
    gy = gyroGet(gyro);
    turnPID(distance);
    delay(20);
  }
  drive(0);
}

void drivePIDTest(int distance){
  turnPID(distance);
}
