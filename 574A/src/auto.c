#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

void autonomous() {
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
