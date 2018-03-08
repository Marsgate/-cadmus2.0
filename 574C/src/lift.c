#include "main.h"

//PID variables
static int prevErr = 0;

void lift(int vel){
  motorSet(LIFT, vel);
}

//lift PID control
void liftPID(int sp){

  double kp = .16;
  double kd = .09;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  speed = error*kp + derivative*kd; // add the values to get the motor speed

  lift(speed); // set the lift to the speed
}
