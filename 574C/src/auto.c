#include "main.h"
#include "lift.h"
#include "arm.h"
#include "scoop.h"
#include "drive.h"
#include "claw.h"
#include "ports.h"
#include "sensorTargets.h"

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


//drive to pylon program =======================================
void conePushStraight(){
  claw(35); //hold preload
  armTarget = AP_MID; // raise arm
  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  scoop(0);
  autoDrive(2300); // drive to pylon

  autoDrive(-400);
  gyTurn(11);
  autoDrive(490); // drive into pylon

  liftTarget = 2100; // move lift to scoring height

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  armTarget = AP_FRONT; // drop arm to score cone

  gyTurn(-18);
}

//drive to pylon program =======================================
void conePushTurn(){
  autoDrive(500); // drive out from wall
  claw(35); //hold preload
  gyTurn(35); // turn to face pylon
  armTarget = AP_MID; // raise arm
  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  scoop(0);
  autoDrive(1450); // drive to pylon

  autoDrive(-400);
  gyTurn(18);
  autoDrive(490); // drive into pylon

  liftTarget = 2100; // move lift to scoring height

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  armTarget = AP_FRONT; // drop arm to score cone
}

// program 1 ===============================================================
void pylon5() {

  conePushTurn(); //drive to pylon
  gyTurn(-18);
  autoDrive(-1353); //reverse to zone
  gyTurn(140);//face the zone

  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = AP_BOT;
  delay(300);

  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(300);
  scoop(0);

  //reverse out of zone
  autoDrive(-370);
}


// program 2 ===============================================================
void pylon20(){
  conePushTurn(); //drive to pylon
  gyTurn(-10);
  autoDrive(-2300); //reverse to zone
  gyTurn(106); // face the zone
  autoDrive(625); // drive in to the zone
  drive(60);
  delay(300);


  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = AP_BOT;
  delay(300);

  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-985);
}


// testing PID ===============================================================
void driveTest(){
  gyTurn(300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}


// control center ===============================================================
void autonomous() {
  gyroReset(gyro);
  liftTarget = analogRead(LIFTPOT); // calibrate the PID starting values
  armTarget = analogRead(ARMPOT);

  //start all tasks
  TaskHandle aHandle = taskRunLoop(armTask, 20); //start arm
  TaskHandle lHandle = taskRunLoop(liftTask, 20); //start lift

  switch(auton){
    case 0:
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon20();
      break;
    case 3:
      autoRight = true;
      pylon5();
      break;
    case 4:
      autoRight = true;
      pylon20();
      break;
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  motorStopAll();
}
