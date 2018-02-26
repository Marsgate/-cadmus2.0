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
  double kp = 0.2;
  double ki = 0.00;
  double kd = 1;
  double kc = 0;

  // define local variables
  int speed; // speed 
  int derivative; // derivative

  int sv = analogRead(ARMPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd + kc; // add the values to get the motor speed

  arm(speed); // set the lift to the speed
}
