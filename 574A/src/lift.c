#include "main.h"
#include "claw.h"

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

void autostackOp(){
  if (joystickGetDigital(1,7,JOY_UP)) {

    bar(127);//start of one
    delay(1425);
    bar(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    bar(-90);
    delay(1525);
    bar(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of one
    bar(127);//start of two
    delay(1300);
    bar(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    bar(-90);
    delay(1400);
    bar(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of two
    bar(127);//start of three
    delay(1100);
    bar(0);
    claw(127);
    delay(450);
    claw(0);
    delay(100);
    bar(-90);
    delay(1200);
    bar(0);
    claw(-127);
    delay(200);
    claw(0);
    delay(100);//end of three

}
}
