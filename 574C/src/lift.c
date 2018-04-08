#include "main.h"

void lift(int vel){
  motorSet(LIFT, vel);
}

void liftPID(int sp){
  double kp = .2;
  double kd = 3;
  static int prevError;

  int sv = analogReadCalibrated(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  int speed = error*kp + prevError*kd;
  prevError = error;

  lift(speed); // set the lift to the speed
}

void liftOp(){
  lift(joystickGetAnalog(2, 3));
}
