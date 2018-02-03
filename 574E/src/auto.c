#include "main.h"
#include "base.h"
#include "drive.h"
#include "claw.h"
#include "chain.h"

void autonomous() {
  base(-127);
  delay(1400);
  base(0);
  drive(127);
  delay(850);
  drive(0);

  base(127);
  delay(1300);
  drive(-60);
  delay(550);
  base(0);
  left(-60);
  right(60);
  delay(700);
  drive(127);
  delay(1000);
  drive(-127);
  delay(500);
  drive(0);
}
