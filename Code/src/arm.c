#include "main.h"
#include "ports.h"

//define coefficients
double a_kp = 5;
double a_ki = 0.2;
double a_kd = 3;


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

  int sv = encoderGet(armEnc); // get sensor value
  int err = sp - sv; // find error
  a_int = a_int + err; // calculate integral

  der = err - a_pre; // calculate the derivative
  a_pre = err; // set current error to equal previous error

  if(err > 10){a_int = 0;} // only modify integral if close to target

  spd = err*a_kp + a_int*a_ki + der*a_kd;; // add the values to get the motor speed

  arm(spd); // set the lift to the speed
}
