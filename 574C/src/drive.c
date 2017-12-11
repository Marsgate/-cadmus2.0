#include "main.h"
#include "ports.h"
#include "math.h"

static int dir;

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
  double ki = 0.1;
  double kd = 3;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  if(abs(error) > 100){
    integral = 0;
  }

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  drive(speed);
}

void turnPID(int sp){
  static int integral = 0;
  static int prevErr = 0;

  double kp = 2.5;
  double ki = 0.05;
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
    int lnew = -lJoy;
    lJoy = -rJoy;
    rJoy = lnew;
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
  while(distance > gy + deadzone || distance < gy - deadzone){
    gy = gyroGet(gyro);
    turnPID(distance);
    delay(20);
  }
  drive(0);
}

void gyTurn(int distance){

  int deadzone = 1;
  gyroReset(gyro);
  int ts = 60; // defualt turn speed

  if(autoRight == true){
    distance = -distance; // inverted turn speed for right auton
  }

  while(1){
    int gy = gyroGet(gyro);
    if(gy < distance - deadzone){
      leftD(ts);
      rightD(-ts);
      dir = 0;
    }else if(gy > distance + deadzone){
      leftD(-ts);
      rightD(ts);
      dir = 1;
    }else{
      if(dir == 0){
        leftD(-5);
        rightD(5);
      }else{
        leftD(5);
        rightD(-5);
      }
      delay(150);
      drive(0);
      break;
    }
  }
}

void drivePIDTest(int distance){
  turnPID(distance);
}
