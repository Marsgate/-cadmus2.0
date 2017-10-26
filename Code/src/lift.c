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

  if(integral > 5000){integral = 5000;} // limit the integral
  if(integral < -5000){integral = -5000;} // limit the integral

  derivative = error - prevError; // calculate the derivative
  prevError = error; // set current error to equal previous error

  //calculate the variables
  double p = error*kp;
  double i = integral*ki;
  double d = derivative*kd;

  //eliminate the integral on the way down
  speed = p + i + d; // add the values to get the motor speed

  lift(speed); // set the lift to the speed

}
