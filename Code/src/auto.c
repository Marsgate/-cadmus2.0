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
  autoDrive(325);
  delay(200);

  //turn to face pylon
  autoTurn(37);
  delay(200);


  armTarget = -70;

  TaskHandle aHandle = taskRunLoop(armTask, 20);

  //hold preload
  claw(40);


  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(150);
  scoop(0);

  delay(700);

  //drive to pylon
  autoDrive(1200);

  //reverse after pushing cones
  autoDrive(-300);

  //turn to face pylon
  gyroReset(gyro);
  while(gyroGet(gyro) < 8){
    leftD(60);
    rightD(-60);
  }

  //drive into pylon
  autoDrive(340);

  liftTarget = 500;
  TaskHandle lHandle = taskRunLoop(liftTask, 20); //start the lift

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  //drop arm to score cone
  armTarget = 0;

  //manual turn
  gyroReset(gyro);
  while(gyroGet(gyro) > -10){
    leftD(-60);
    rightD(60);
  }

  autoDrive(-1100); //reverse to zone

  //face the zone
  autoTurn(170);


  //drive into the zone
  //autoDrive(200);

  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = -80;
  delay(300);

  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(300);
  scoop(0);

  //reverse out of zone
  autoDrive(-300);

  taskDelete(lHandle);
  taskDelete(aHandle);
  motorStopAll();
}

// testing PID ===============================================================
void driveTest(){
  autoTurn(300);
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
    case 2:
      driveTest();
  }
}
