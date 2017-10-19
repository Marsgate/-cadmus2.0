#include "API.h"
#include "ports.h"

//define coefficients
int kp = 1;
int ki = 1;
int kd = 1;

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

void liftPID(int sp, int sv){
  int error = sp - sv;
  integral = integral + error;
  derivative = error - prevError;
  prevError = error;
  int speed = error*kp + integral*ki + derivative*kd;
  lift(speed);
}
