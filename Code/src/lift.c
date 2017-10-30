#include "API.h"
#include "ports.h"

//PID variables
static int integral = 0;
static int prevErr = 0;

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
  /* old coeffecients
  double kp = .17;
  double ki = .003;
  double kd = .8;
  */

  //define coefficients
  double kp = .27;
  double ki = 0.02;
  double kd = 0.2;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  if(error > 200){integral = 0;} // only modify integral if close to target

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  lift(speed); // set the lift to the speed
}
