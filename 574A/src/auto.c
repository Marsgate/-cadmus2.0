#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

<<<<<<< HEAD
void autonomous() {
<<<<<<< HEAD
=======
void leftPylon20() {
>>>>>>> parent of 1611f92... Autonomous Both sides, Phase 2.5 code
  lift(127); //lift rises for 2.5 seconds then stop
=======
  lift(127); //lift rises for 2.5 seconds then stops
  delay(2000);
  lift(0);
>>>>>>> parent of 62142b7... Autonomous Phase 2
  drive(127);
  antitip(-127);
  delay(1250);
  antitip(0);
  delay(2250);
  drive(0);
  pylon(127);
  delay(2500);
  pylon(0);
  drive(-127);
  delay(3000);
  drive(0);
  right(127);
  left(-127);
  delay(250);
  right(0);
  left(0);
  drive(-127);
  delay(500);
  drive(0);
  right(127);
  left(-127);
  delay(250);
  right(0);
  left(0);
  drive(127);
  delay(1250);
  drive(0);
  antitip(127);
  delay(1100);
  antitip(0);
  drive(-127);
  delay(1250);
  motorStopAll();
}
<<<<<<< HEAD
=======

void CenterStack(){
  lift(127);
  delay(2000);
  lift(0);
  delay(100);
  drive(127);
  delay(400);
  drive(0);
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

void autonomous() {
  switch(auton){
    case 0:
      break; //dont run auto
    case 1:
      leftPylon20();
      break;
    case 2:
      CenterStack();
      break;
  }
}
>>>>>>> parent of 1611f92... Autonomous Both sides, Phase 2.5 code
