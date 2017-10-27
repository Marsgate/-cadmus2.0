#include "main.h"
#include "ports.h"

//define coefficients
double kp = 0;
double ki = 0;
double kd = 0;


//define global variables
int integral = 0;
int derivative = 0;
int prevError = 0;

#define I_LIM 12000 // integral limit

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
  int speed; // define for later

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  //if(integral > I_LIM){integral = I_LIM;} // limit the integral
  //if(integral < -I_LIM){integral = -I_LIM;} // limit the integral

  derivative = error - prevError; // calculate the derivative
  prevError = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd;; // add the values to get the motor speed

  arm(speed); // set the lift to the speed

}
