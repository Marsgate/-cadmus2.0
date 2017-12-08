#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"

void autonomous() {
  drive(127);
  delay(2000);
  drive(0);
  motorStopAll();
}
