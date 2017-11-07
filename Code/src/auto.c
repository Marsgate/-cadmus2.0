#include "main.h"
#include "lift.h"
#include "arm.h"
#include "scoop.h"
#include "drive.h"
#include "claw.h"

void ltLow(){
  liftPID(400);
}

void lt350(){
  liftPID(350);
}

void ati60(){
  armPID(-60);
}

void at0(){
  armPID(0);
}

void autonomous() {

  //match autonomous

  /*pseudo code
  raise the chainbar + lift a little
  lower the pylon grabber
  reverse to the first pylon
  raise pylon grabber
  stack the preload
  drive forward
  slant to center
  spin to face the zone
  reverse
  lower pylon grabber
  drive forward
  */

  //start lift and arm PID
  TaskHandle lHandle = taskRunLoop(ltLow, 20);
  TaskHandle aHandle = taskRunLoop(ati60, 20);

  claw(30);

  delay(700);

  scoop(-127);
  delay(1400);
  scoop(0);

  autoDrive(1200); //rough estimate to drive to pylon

  scoop(127);
  delay(1400);
  aHandle = taskRunLoop(at0, 20);
  delay(600);

  claw(-127);
  delay(400);

  claw(0);

  motorStopAll();
  taskDelete(lHandle);
  taskDelete(aHandle);
}
