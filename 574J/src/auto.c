
#include "main.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "drive.h"


void autonomous() {
  claw(60);
  drive(127);
  delay(500);
  drive(0);
  delay(200);
  delay(100);
  lift(127);
  delay(1600);
  lift(0);

  drive(127);
  delay(300); //drive distance
  drive(0);
  lift(-60);
  delay(500);
  lift(0);
  delay(400);

  claw(-127);
  delay(200);
  lift(127);
  delay(300);
  claw(0);
  delay(300);
  lift(0);
  drive(-60);
  delay(500);
  drive(0);
  motorStopAll();

}
