#include "main.h"
#include "ports.h"

//PID variables
static int integral = 0;
static int prevErr = 0;

// motion control for the arm
void arm(int vel){
  motorSet(ARM1, vel);
  motorSet(ARM2, vel);
}

//arm PID control (basically copy pasted from liftPID)
void armPID(int sp){
  //define coefficients
  double kp = 0.17;
  double ki = 0.0005;
  double kd = 0.4;

  // define local variables
  int speed; // speed
  int derivative; // derivative

  int sv = analogRead(ARMPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  arm(-speed); // set the lift to the speed
}

void armOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    arm(127);
  }else if(joystickGetDigital(1, 6, JOY_DOWN)){
    arm(-127);
  }
}
