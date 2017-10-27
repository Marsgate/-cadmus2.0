#include "API.h"
#include "ports.h"

//define coefficients
double kp = 0.17;
double ki = 0.003;
double kd = .8;


//define global variables
int integral = 0;
int derivative = 0;
int prevError = 0;

#define I_LIM 5000 // integral limit

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
  int speed; // define for later

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  if(integral > I_LIM){integral = I_LIM;} // limit the integral
  if(integral < -I_LIM){integral = -I_LIM;} // limit the integral

  derivative = error - prevError; // calculate the derivative
  prevError = error; // set current error to equal previous error

  speed = error*kp + integral*ki + derivative*kd;; // add the values to get the motor speed

  lift(speed); // set the lift to the speed
}
