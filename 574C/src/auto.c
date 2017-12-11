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
void conePush(){
  autoDrive(550); // drive out from wall
  delay(100);
  gyTurn(33); // turn to face pylon
  armTarget = AP_MID; // raise arm
  claw(25); //hold preload
  delay(350);
  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(100);
  scoop(0);
  delay(300); // wait for other tasks to reach their end point
  autoDrive(1500); // drive to pylon

  delay(100);
  autoDrive(-400);
  delay(100);
  gyTurn(10);
  autoDrive(480); // drive into pylon

  liftTarget = 2200; // move lift to scoring height

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  armTarget = AP_FRONT; // drop arm to score cone

  gyTurn(-16);
}

//drive to pylon program =======================================
void PyDrive(){
  autoDrive(400); // drive out from wall
  delay(200);
  gyTurn(38); // turn to face pylon
  armTarget = AP_MID; // raise arm
  claw(40); //hold preload
  delay(400);
  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(150);
  scoop(0);
  delay(400); // wait for other tasks to reach their end point
  autoDrive(1600); // drive to pylon

  liftTarget = 2200; // move lift to scoring height

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  armTarget = AP_FRONT; // drop arm to score cone

  gyTurn(-10);
}


// program 1 ===============================================================
void pylon5() {

  conePush(); //drive to pylon
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
  conePush(); //drive to pylon
  autoDrive(-1675); //reverse to zone
  gyTurn(40);// parallel to the zone
  autoDrive(-720); // center the robot
  gyTurn(85); // face the zone
  autoDrive(675); // drive in to the zone
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
