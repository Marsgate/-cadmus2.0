#include "main.h"
#include "base.h"
#include "drive.h"
#include "claw.h"
#include "chain.h"

void autonomous() {
  base(127);
  delay(1500);
  drive(127);
  delay(1000);
  drive(0);
  base(-127);
  delay(1200);
  drive(-60);
  delay(400);
  base(0);
  left(-60);
  right(60);
  delay(500);
  drive(127);
  delay(700);
  drive(-127);
  delay(500);
  drive(0);
}
