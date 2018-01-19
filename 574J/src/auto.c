
#include "main.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "drive.h"
#include "arm.h"

void autonomous() {
  arm(-75);
  lift(107);
  delay(1000);
  arm(0);
  lift(0);
  drive(-127);
  delay(530);
  drive(0);
  arm(-75);
  delay(800);
  arm(0);
  claw(-127);
  delay(250);
  claw(60);
  drive(127);
  delay(200);
  drive(0);
  arm(127);
  delay(1000);
  claw(0);
  arm(0);

}
