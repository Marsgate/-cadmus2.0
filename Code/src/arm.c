#include "main.h"
#include "ports.h"

//define coefficients
double a_kp = 0;
double a_ki = 03;
double a_kd = 0;


//define global variables
int a_int = 0;
int a_pre = 0;

//reset the encoder if the arm bottoms out
void armTest(){
  if(digitalRead(ARM_LIMIT) == LOW){
    encoderReset(armEnc);
  }
}

// motion control for the arm
void arm(int vel){
  motorSet(ARM, vel);
}

//arm PID control (basically copy pasted from liftPID)
void armPID(int sp){
  // define local variables
  int spd; // speed
  int der; // derivative
  int i_lim = 5000; // integral limit

  int sv = analogRead(LIFTPOT); // get sensor value
  int err = sp - sv; // find error
  a_int = a_int + err; // calculate integral

  if(a_int > i_lim){a_int = i_lim;} // limit the integral
  if(a_int < -i_lim){a_int = -i_lim;} // limit the integral

  der = err - a_pre; // calculate the derivative
  a_pre = err; // set current error to equal previous error

  spd = err*a_kp + a_int*a_ki + der*a_kd;; // add the values to get the motor speed

  arm(spd); // set the lift to the speed
}
