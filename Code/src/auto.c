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
void leftPylon() {
  encoderReset(armEnc);

  //drive out from wall
  autoDrive(285);
  delay(200);

  //turn to face pylon
  autoTurn(160, 60);
  delay(200);

  liftTarget = 600;

  armTarget = -60;

  TaskHandle lHandle = taskRunLoop(liftTask, 20);
  TaskHandle aHandle = taskRunLoop(armTask, 20);

  //hold preload
  claw(30);

  delay(200); // wait for lift to raise

  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(300);
  scoop(0);

  //drive to pylon
  autoDrive(1000);
  delay(200);

  //reverse after pushing cones
  autoDrive(-230);
  delay(200);

  //turn to face pylon
  autoTurn(60, 60);
  delay(200);

  //drive into pylon
  autoDrive(370);


  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  //drop arm to score cone
  armTarget = 0;
  delay(200);

  autoTurn(-40, 60); //turn to face zone
  delay(200);

  autoDrive(-1200); //reverse to zone

  //face the zone
  autoTurn(100, 60);
  autoDrive(-150);
  autoTurn(370, 60);

  //drive into the zone
  //autoDrive(200);

  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = -60;

  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(300);
  scoop(0);

  //reverse out of zone
  autoDrive(-500);



  taskDelete(lHandle);
  taskDelete(aHandle);
  motorStopAll();
}

// testing PID ===============================================================
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
      leftPylon();
      break;
  }
}
