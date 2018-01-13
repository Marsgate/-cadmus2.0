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


void autostackofOp(){
if((joystickGetDigital(1, 7, JOY_UP)==1))// #1 off of field
{

}
if((joystickGetDigital(1, 5, JOY_UP)==1))//#2 off of field
{

}
if((joystickGetDigital(1, 5, JOY_DOWN)==1))//#3 off of field
{

}
if((joystickGetDigital(1, 7, JOY_LEFT)==1))//#4 off the field
{

}
if((joystickGetDigital(1, 7, JOY_DOWN)==1))//#5 off the field
{

}
if((joystickGetDigital(1, 7, JOY_RIGHT)==1))//#6 off the field
{

}
if((joystickGetDigital(1, 8, JOY_LEFT)==1))//#7 off the field
{

}
if((joystickGetDigital(1, 8, JOY_UP)==1))//#8 off the field
{

}
if((joystickGetDigital(1, 7, JOY_RIGHT)==1))//#9 off the field
{

}

}

void autostackpOp(){
  if((joystickGetDigital(1, 7, JOY_LEFT)==1))// group 1
  {
    pylon(-127);
    delay(410);
    pylon(0);
    bar(127);
    delay(1400);
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
    claw(0);// End of #1
    bar(127);
    delay(1200);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(1050);
    bar(0);
    claw(127);
    delay(300);
    claw(0);// end of #2
    bar(127);
    delay(1000);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(900);
    bar(0);
    claw(127);
    delay(300);
    claw(0);// end of #3

  }
  if((joystickGetDigital(1, 7, JOY_UP)==1))//group 2
  {
    pylon(127);
    delay(410);
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
    claw(0);// end of #4
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
    claw(0);// end of #5

  }

  if((joystickGetDigital(1, 7, JOY_RIGHT)==1))//group 3
  {
    bar(127);
    lift(127);
    delay(500);
    lift(0);
    delay(850);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(900);
    bar(0);
    claw(127);
    delay(300);
    claw(0);// end of #6
    bar(127);
    lift(127);
    delay(750);
    lift(0);
    delay(850);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(900);
    bar(0);
    claw(127);
    delay(300);
    claw(0);//end of #7
    bar(127);
    lift(127);
    delay(900);
    lift(0);
    delay(850);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(900);
    bar(0);
    claw(127);
    delay(300);
    claw(0);// end of #8
    bar(127);
    lift(127);
    delay(1050);
    lift(0);
    delay(850);
    bar(0);
    claw(-127);
    delay(250);
    bar(-127);
    delay(250);
    claw(0);
    delay(900);
    bar(0);
    claw(127);
    delay(300);
    claw(0);// of #9
  }
}
