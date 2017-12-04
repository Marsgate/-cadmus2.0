#include "API.h"
#include "ports.h"

//PID variables
static int integral = 0;
static int prevErr = 0;
static int liftOpTarget = 700;

void lift(int vel){
  motorSet(LIFT1, vel);
  motorSet(LIFT2, vel);
}

//lift PID control
void liftPID(int sp){

  double kp = .15;
  double ki = .007;
  double kd = .16 ;

  // define local  variables
  int speed; // speed
  int derivative; // derivative

  int sv = analogRead(LIFTPOT); // get sensor value
  int error = sp - sv; // find error
  integral = integral + error; // calculate integral

  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error

  if(error > 100){integral = 0;} // only modify integral if close to target

  speed = error*kp + integral*ki + derivative*kd; // add the values to get the motor speed

  lift(speed); // set the lift to the speed
}

void liftOp(){
  if (joystickGetDigital(1,5,JOY_UP)){
    lift(127);
    liftOpTarget = analogRead(LIFTPOT);
  }else if (joystickGetDigital(1, 5, JOY_DOWN)){
    lift(-127);
    liftOpTarget = analogRead(LIFTPOT);
  }else{
    liftPID(liftOpTarget);
  }
}
