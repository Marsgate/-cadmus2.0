#include "main.h"

//PID variables
static int integral = 0;
static int prevErr = 0;

void lift(int vel){
  motorSet(LIFT, vel);
}

//lift PID control
void liftPID(int sp){

  double kp = .15;
  double ki = .000;
  double kd = .1;
  double kc = 0;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  if(error > 100){integral = 0;} // only modify integral if close to target

  speed = error*kp + integral*ki + derivative*kd + kc; // add the values to get the motor speed

  lift(speed); // set the lift to the speed
}
