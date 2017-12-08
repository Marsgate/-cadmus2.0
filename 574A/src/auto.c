#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

void autonomous() {
  lift(127); //lift rises for 2.5 seconds then stops
  delay(2000);
  lift(0);
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
