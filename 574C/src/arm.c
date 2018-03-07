#include "main.h"
#include "ports.h"

// motion control for the arm
void arm(int vel){
  motorSet(ARM1, vel);
  motorSet(ARM2, vel);
}

//arm PID control (basically copy pasted from liftPID)
void armPID(int sp){
  //define coefficients
  double kp = .2;
  double kd = .8;

  // define variables
  int speed; // speed
  int derivative; // derivative
  static int prevErr = 0;

  int sv = analogRead(ARMPOT); // get sensor value
  int error = sp - sv; // find error


  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + derivative*kd; // add the values to get the motor speed

  arm(speed); // set the lift to the speed
}
