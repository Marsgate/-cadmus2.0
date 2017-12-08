#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

void autonomous() {
  drive(127);
  delay(1000);
  drive(0);

  motorStopAll();
}
