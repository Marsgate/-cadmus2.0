#include "API.h"
#include "ports.h"

//define coefficients
double l_kp = 0.17;
double l_ki = 0.003;
double l_kd = .8;

//define global variables
int l_int = 0;
int l_pre = 0;


void lift(int vel){
  motorSet(LIFT1, vel);
  motorSet(LIFT2, vel);
}

void liftOp(){
  if (joystickGetDigital(1,5,JOY_UP)){
    lift(127);
  }else if (joystickGetDigital(1, 5, JOY_DOWN)){
    lift(-127);
  }else{
    lift(0);
  }
}

//lift PID control
void liftPID(int sp){
  // define local variables
  int spd; // speed
  int der; // derivative
  int i_lim = 5000; // integral limit

  int sv = analogRead(LIFTPOT); // get sensor value
  int err = sp - sv; // find error
  l_int = l_int + err; // calculate integral

  if(l_int > i_lim){l_int = i_lim;} // limit the integral
  if(l_int < -i_lim){l_int = -i_lim;} // limit the integral

  der = err - l_pre; // calculate the derivative
  l_pre = err; // set current error to equal previous error

  spd = err*l_kp + l_int*l_ki + der*l_kd;; // add the values to get the motor speed

  lift(spd); // set the lift to the speed
}
