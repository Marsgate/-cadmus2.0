#include "main.h"
#include "claw.h"

void lift(int vel){
  motorSet(LIFT1, vel);

}

void liftOp(){
  if(joystickGetDigital(1,6, JOY_UP)){
    lift(127);
  }else if(joystickGetDigital(1,6, JOY_DOWN)){
    lift(-127);
  }else{
    lift(0);
  }
}
void bar(int vel){
  motorSet(LIFT2, vel);
}
void barOp(){
  bar(joystickGetAnalog(1,3));

}
void autostackOp(){
  while(1){bar(127);
  delay(550);
  claw(127);
  delay(200);
  bar(0);
  claw(0);
  delay(50);
  bar(-127);
  delay(550);
  claw(-127);
  delay(200);
  bar(0);
  claw(0);
  delay(50);
  if (joystickGetDigital(1, 8, JOY_LEFT)) {
    break;
    delay(20);

  }
}

}
