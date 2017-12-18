#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "gyro.h"
#include "liftz.h"

void Test(){
  drive0(127);
  delay(10000);
  drive0(0);
}
void left0Pylon20(){
  antitip(127);
  delay(1200);
  antitip(0);
  bar(127);
  delay(1300);
  bar(0);
  drive0(127);
  delay(600);
  delay(1800);
  drive0(0);
  pylon(127);
  delay(1500);
  pylon(0);
  delay(100);
  drive0(-70);
  delay(1500);
  drive0(0);
  delay(100);
right0(127);
left0(-127);
delay(750);
drive0(0);
delay(100);
drive0(127);
delay(450);
drive0(0);
  pylon(-127);
  delay(1200);
  pylon(0);
  delay(100);
  drive0(-127);
  delay(750);
  motorStopAll();
}
void right0Pylon20() {
  lift(127); //lift rises for 2.5 seconds then stop
  drive0(127);
  antitip(127);
  delay(1000);
  antitip(0);
  delay(1000);
  lift(0);
  delay(500);
  drive0(0);
  delay(100);
  pylon(127);
  delay(1500);
  pylon(0);
  delay(100);
  drive0(-127);
  delay(2000);
  drive0(0);
  delay(100);
  gyroturn(-50);
  drive0(-127);
  delay(750);
  drive0(0);
  delay(100);
  gyroturn(-55);
  drive0(127);
  delay(1550);
  drive0(0);
  delay(100);
  antitip(-127);
  delay(1100);
  antitip(0);
  drive0(-127);
  delay(1450);
  motorStopAll();
}

void CenterStackL(){
  lift(127);
  delay(2000);
  lift(0);
  delay(100);
  gyroturn(45);
  drive0(127);
  antitip(127);
  delay(1000);
  antitip(0);
  delay(500);
  drive0(0);
  lift(-127);
  delay(750);
  lift(0);
  claw(-127);
  delay(250);
  claw(0);
  drive0(-127);
  delay(500);
  drive0(0);
}
void CenterStackR() {

    lift(127);
    delay(2000);
    lift(0);
    delay(100);
    left0(-127);
    right0(127);
    delay(250);
    drive0(0);
    delay(100);
    drive0(127);
    antitip(127);
    delay(1000);
    antitip(0);
    delay(500);
    drive0(0);
    lift(-127);
    delay(750);
    lift(0);
    claw(-127);
    delay(250);
    claw(0);
    drive0(-127);
    delay(500);
    drive0(0);
}
void autonomous() {
  switch(auton){
    case 0:
      break; //dont run auto
    case 1:
      left0Pylon20();
      break;
    case 2:
      CenterStackL();
      break;
      case 3:
      CenterStackR();
      break;
      case 4:
      right0Pylon20();
      break;
      case 5:
      Test();
      break;
  }
}
