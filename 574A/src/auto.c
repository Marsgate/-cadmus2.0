#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "gyro.h"
#include "liftz.h"

void Test(){
  drive(127);
  delay(10000);
  drive(0);
}
void leftPylon20(){
  antitip(127);
  delay(1200);
  antitip(0);
  bar(127);
  delay(1300);
  bar(0);
  drive(127);
  delay(600);
  delay(1800);
  drive(0);
  pylon(127);
  delay(1500);
  pylon(0);
  delay(100);
  drive(-70);
  delay(1500);
  drive(0);
  delay(100);
right(127);
left(-127);
delay(750);
drive(0);
delay(100);
drive(127);
delay(450);
drive(0);
  pylon(-127);
  delay(1200);
  pylon(0);
  delay(100);
  drive(-127);
  delay(750);
  motorStopAll();
}
void rightPylon20() {
  lift(127); //lift rises for 2.5 seconds then stop
  drive(127);
  antitip(127);
  delay(1000);
  antitip(0);
  delay(1000);
  lift(0);
  delay(500);
  drive(0);
  delay(100);
  pylon(127);
  delay(1500);
  pylon(0);
  delay(100);
  drive(-127);
  delay(2000);
  drive(0);
  delay(100);
  gyroturn(-50);
  drive(-127);
  delay(750);
  drive(0);
  delay(100);
  gyroturn(-55);
  drive(127);
  delay(1550);
  drive(0);
  delay(100);
  antitip(-127);
  delay(1100);
  antitip(0);
  drive(-127);
  delay(1450);
  motorStopAll();
}

void CenterStackL(){
  lift(127);
  delay(2000);
  lift(0);
  delay(100);
  gyroturn(45);
  drive(127);
  antitip(127);
  delay(1000);
  antitip(0);
  delay(500);
  drive(0);
  lift(-127);
  delay(750);
  lift(0);
  claw(-127);
  delay(250);
  claw(0);
  drive(-127);
  delay(500);
  drive(0);
}
void CenterStackR() {

    lift(127);
    delay(2000);
    lift(0);
    delay(100);
    left(-127);
    right(127);
    delay(250);
    drive(0);
    delay(100);
    drive(127);
    antitip(127);
    delay(1000);
    antitip(0);
    delay(500);
    drive(0);
    lift(-127);
    delay(750);
    lift(0);
    claw(-127);
    delay(250);
    claw(0);
    drive(-127);
    delay(500);
    drive(0);
}
void autonomous() {
  switch(auton){
    case 0:
      break; //dont run auto
    case 1:
      leftPylon20();
      break;
    case 2:
      CenterStackL();
      break;
      case 3:
      CenterStackR();
      break;
      case 4:
      rightPylon20();
      break;
      case 5:
      Test();
      break;
  }
}
