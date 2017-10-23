#include "API.h"
#include "ports.h"

//define coefficients
float kp = .17;
float ki = .004;
float kd = .6;

//define global variables
int integral = 0;
int derivative = 0;
int prevError = 0;

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
  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral
  if(integral > 12000){integral = 12000;} // limit the integral
  derivative = error - prevError; // calculate the derivative
  prevError = error; // set current error to equal previous error
  int speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed
  lift(speed); // set the lift to the speed
}
