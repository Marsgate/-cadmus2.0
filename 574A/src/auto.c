#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

void rightPylon20(){
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
  right(-127);
  left(127);
  delay(300);
  right(0);
  left(0);
  delay(100);
  drive(-127);
  delay(750);
  drive(0);
  delay(100);
  right(-127);
  left(127);
  delay(350);
  right(0);
  left(0);
  delay(100);
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
void leftPylon20() {
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
  right(127);
  left(-127);
  delay(300);
  right(0);
  left(0);
  delay(100);
  drive(-127);
  delay(750);
  drive(0);
  delay(100);
  right(127);
  left(-127);
  delay(350);
  right(0);
  left(0);
  delay(100);
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
  left(127);
  right(-127);
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
  }
}
