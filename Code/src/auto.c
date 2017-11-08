#include "main.h"
#include "lift.h"
#include "arm.h"
#include "scoop.h"
#include "drive.h"
#include "claw.h"
#include "ports.h"

//PID targets
static int liftTarget = 0;
static int armTarget = 0;

//PID tasks
void liftTask(){
  liftPID(liftTarget);
}
void armTask(){
  armPID(armTarget);
}


// program 1 ===============================================================
void pylonLeft() {

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

  liftTarget = 400;
  armTarget = -60;

  TaskHandle lHandle = taskRunLoop(liftTask, 20);
  TaskHandle aHandle = taskRunLoop(armTask, 20);

  claw(20);

  delay(200); // wait for lift to raise

  scoop(-127);
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  scoop(0);

  autoDrive(1100); //rough estimate to drive to pylon

  autoTurn(100, 60);
  /*
  scoop(127);
  delay(1400);
  armTarget = 0;
  delay(600);
  */

  taskDelete(lHandle);
  taskDelete(aHandle);
  motorStopAll();
  while(1);
}

void driveTest(){
  autoDrive(1300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}

// control center ===============================================================
void autonomous() {
  switch(auton){
    case 0:
      break; //dont run auton
    case 1:
      driveTest();
      break;
  }
}
