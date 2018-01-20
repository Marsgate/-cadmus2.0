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

void autostacko(){
    bar(127);
    delay(1500);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1350);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of 1
    pylon(-127);
    delay(210);
    pylon(0);
    bar(127);
    delay(1400);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1250);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of 2
    bar(127);
    delay(1400);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1250);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of 3
    pylon(127);
    delay(210);
    pylon(0);
    bar(127);
    delay(1300);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1100);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of 4
    bar(127);
    lift(127);
    delay(250);
    lift(0);
    delay(1000);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1100);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of 5

}


  void autoalignp(){
    if((joystickGetDigital(1, 5, JOY_UP))==1){
      claw(-127);
      delay(350);
      bar(-90);
      delay(200);
      claw(0);

  while(analogRead(ARMPOT) <3800){
      bar(-127);
  }
      bar(40);
  }
  }

void autobar(int sp){
  double kp = 0.25;
  int sv = analogRead(ARMPOT);
  int error = sp-sv;
  int speed = error*kp;
  bar(-speed);
}
