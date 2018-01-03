#include "main.h"
#include "ports.h"
#include "math.h"

static int br = 10;
static int dir;


//generic drive functions =============================================
void leftD(int vel){
  motorSet(DRIVEL1, vel);
  motorSet(DRIVEL2, vel);
}
void rightD(int vel){
  motorSet(DRIVER1, vel);
  motorSet(DRIVER2, vel);
}
void drive(int vel){
  motorSet(DRIVEL1, vel);
  motorSet(DRIVEL2, vel);
  motorSet(DRIVER1, vel);
  motorSet(DRIVER2, vel);
}


//PID functions =============================================
void drivePID(int sp){
  static int integral = 0;
  static int prevErr = 0;

  double kp;
  double ki;
  double kd;

  //change the constants based on distance
  if(abs(sp) > 400){
    kp = .25;
    ki = .0;
    kd = .9;
  }else{
    kp = .35;
    ki = .0;
    kd = 1.2;
  }

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  if(abs(error) > 200){
    integral = 0;
  }

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  if(speed > 127){
    speed = 127;
  }else if(speed < -127){
    speed = -127;
  }

  drive(speed);
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

  leftD(left);
  rightD(right);
}

// autonomous drive functions =============================================

// forward and backward
void autoDrive(int distance){
  int timer = 0;
  int encAvg = 0;
  int deadzone = 5;
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  while(distance > encAvg + deadzone || distance < encAvg - deadzone || timer > 1000){
    encAvg = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;
    drivePID(distance);
    if(abs(distance - encAvg) < 50){
      timer += 20;
    }
    delay(20);
    lcdPrint(uart1, 1, "left: %d", encoderGet(driveEncLeft));
		lcdPrint(uart1, 2, "right: %d", encoderGet(driveEncRight));
  }
  if(distance > 0){
    drive(-br);
  }else{
    drive(br);
  }
  delay(150);
  drive(0);
}


void gyTurn(int distance){

  int deadzone = 1;
  int ts = 80; // defualt turn speed

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
        leftD(-br);
        rightD(br);
      }else{
        leftD(br);
        rightD(-br);
      }
      delay(150);
      drive(0);
      break;
    }
  }
}
