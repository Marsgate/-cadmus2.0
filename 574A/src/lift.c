#include "main.h"
#include "claw.h"
#include "pylon.h"

void lift(int vel){
  motorSet(LIFT1, vel);

}

void liftOp(){
  if(joystickGetDigital(1, 6, JOY_UP)){
    lift(127);
  }else if(joystickGetDigital(1,6,JOY_DOWN)){
    lift(-127);
  }else{
    lift(0);
  }
}

void bar(int vel){
    motorSet(LIFT2, vel);
}
void barOp(){
    bar(-joystickGetAnalog(1,3));
}


void autobar(int sp){
  double kp = 0.25;
  int sv = analogRead(ARMPOT);
  int error = sp-sv;
  int speed = error*kp;
  bar(-speed);
}
