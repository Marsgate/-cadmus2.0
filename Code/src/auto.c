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


//drive to pylon program =======================================
void leftPyDrive(){
  autoDrive(325); // drive out from wall
  delay(200);
  autoTurn(39); // turn to face pylon
  armTarget = 2000; // raise arm
  claw(40); //hold preload

  scoop(-127); //drop pylon scoop
  // delay until scoop bottoms out
  while(digitalRead(SCOOP_LIM_BOT) == HIGH){
    delay(20); //delay to make room for the other tasks to run
  }
  delay(150);
  scoop(0);
  delay(400); // wait for other tasks to reach their end point
  autoDrive(1200); // drive to pylon
  autoDrive(-300); // reverse after pushing cones

  //turn to face pylon
  gyroReset(gyro);
  while(gyroGet(gyro) < 10){
    leftD(60);
    rightD(-60);
  }

  autoDrive(340); //drive into pylon
  liftTarget = 2200; // move lift to scoring height

  scoop(127); //raise scoop
  while(digitalRead(SCOOP_LIM_TOP) == HIGH){
    delay(20);
  }
  scoop(0);

  armTarget = 15; // drop arm to score cone

  //face the robot toward the scoring zone
  gyroReset(gyro);
  while(gyroGet(gyro) > -7){
    leftD(-60);
    rightD(60);
  }

}


// program 1 ===============================================================
void leftPylon5() {

  leftPyDrive(); //drive to pylon
  autoDrive(-1100); //reverse to zone
  autoTurn(170);//face the zone

  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = 2000;
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
}


// program 2 ===============================================================
void leftPylon20(){
  leftPyDrive(); //drive to pylon
  autoDrive(-1200); //reverse to zone
  autoTurn(40);// parallel to the zone
  autoDrive(-600); // center the robot
  autoTurn(90); // face the zone
  autoDrive(550); // drive in to the zone
  drive(60);
  delay(300);


  //release the cone
  claw(-127);
  delay(300);
  claw(-30);
  armTarget = 2000;
  delay(300);

  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-800);
}


// testing PID ===============================================================
void driveTest(){
  autoTurn(300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}


// control center ===============================================================
void autonomous() {
  liftTarget = analogRead(LIFTPOT); // calibrate the PID starting values
  armTarget = analogRead(ARMPOT);

  //start all tasks
  TaskHandle aHandle = taskRunLoop(armTask, 20); //start arm
  TaskHandle lHandle = taskRunLoop(liftTask, 20); //start lift

  switch(auton){
    case 0:
      break; //dont run auton
    case 1:
      leftPylon5();
      break;
    case 2:
      leftPylon20();
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  motorStopAll();
}
