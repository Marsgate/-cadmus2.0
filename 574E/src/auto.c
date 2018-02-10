#include "main.h"
#include "base.h"
#include "drive.h"


void autonomous() {
  base(127);// Drops in begging
  delay(1500);
  drive(127);// Drives to mobile base
  delay(0);
  drive(0);
  base(-127);
  delay(0);
  drive(-60);
  delay(0);
  base(0);
  left(-60);
  right(60);
  delay(0);
  drive(127);
  delay(0);
  drive(-127);
  delay(0);
  drive(0);
drive();
}
drive();
}
