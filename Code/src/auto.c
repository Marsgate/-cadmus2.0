#include "main.h"
#include "lift.h"
#include "arm.h"
#include "scoop.h"
#include "drive.h"

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

  /*
  int timer = 0;
  while(timer < 700){
    liftPID(1000);
    delay(20);
    arm(-127);
    timer += 20;
  }

  arm(0);
  timer = 0;
  scoop(-127);
  delay(700);
  */
  autoTurn(-300, 80);
  motorStopAll();
  while(1);
}
