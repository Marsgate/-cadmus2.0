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
static int clawTarget = -1000;

//PID tasks
void liftTask(){
  liftPID(liftTarget);
}
void armTask(){
  armPID(armTarget);
}
void clawTask(){
  clawGrip(clawTarget);
}

//drive to pylon program =======================================
void pickUp(){
  clawTarget = 127; // close claw
  armTarget = AP_AUTO; // raise arm
  liftTarget = LP_BOT;
  autoScoop(0); // deploy scoop
  sonarDrive(); //go get pylon
  autoScoop(1); // bring scoop up
  armTarget = AP_FRONT; // drop arm to score cone
  delay(400);
  clawTarget = -127; // open claw
  while(analogRead(CLAWPOT) < CP_OPEN) delay(20);
  armTarget = AP_AUTO;
}

// program 1 ===============================================================
void pylon5() {

  pickUp(); //drive to pylon
  autoDrive(-700);
  gyTurn(-180);//face the zone
  autoScoop(0);

  //reverse out of zone
  autoDrive(-300);
}


// program 2 ===============================================================
void pylon20(){
  pickUp(); //drive to pylon
  autoDrive(-1100);
  gyTurn(-132);//face the zone
  autoDrive(210);
  gyTurn(-222);

  drive(-127);
  delay(650);
  drive(-60);
  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-600);
  gyTurn(-398);

}

void skills(){
  pylon20();
  gyroReset(gyro);
  //RED 10 point /////////////////////////////////////////////////////

  //grab the first pylon
  autoScoop(0);
  sonarDrive();
  autoScoop(1);

  //face zone
  autoDrive(-400);
  gyroReset(gyro);
  gyTurn(160);

  //manual drop
  drive(-40);
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone

  autoDrive(-300);


  //BLUE 20 point /////////////////////////////////////////////////////
  // next pylon
  gyroReset(gyro);
  gyTurn(-156);
  autoScoop(0);
  sonarDrive();
  autoScoop(1);

  //turn parallel to zone
  autoDrive(650);
  gyTurn(-272);
  autoDrive(300);

  //align with zone
  gyTurn(-185);
  autoDrive(500); // drive in to the zone
  drive(-60);

  scoop(-127); //drop pylon scoop
  delay(1000);
  autoDrive(-450);
  scoop(0);

  //reverse out of zone




  //BLUE 10 point /////////////////////////////////////////////////////

  // next pylon
  gyroReset(gyro);
  autoScoop(0);
  gyTurn(-157);
  sonarDrive();
  autoScoop(1);

  //face zone
  autoDrive(-400);
  gyroReset(gyro);
  gyTurn(150);
  autoDrive(150);
  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-300);


  //10 /////////////////////////////////////////////////////////

  gyroReset(gyro);
  gyTurn(-160);
  autoScoop(0);
  sonarDrive();
  autoScoop(1);
  //turn parallel to zone

  autoDrive(900);

  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-300);


  //FINAL /////////////////////////////////////////////////////////
  //face next pylon
  autoScoop(0);
  gyroReset(gyro);
  gyTurn(80);
  autoDrive(225);
  gyTurn(118);
  sonarDrive();
  autoScoop(1);

  //go score
  autoDrive(-400);
  gyTurn(270);
  autoDrive(800);
  gyTurn(350);
  autoDrive(150);

  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-150);
  gyroReset(gyro);
  gyTurn(100);
  autoDrive(1000);
}

// testing PID ===============================================================
void driveTest(){
  gyTurn(300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}

void ram(){
  autoDrive(5000);
}

void tower(){
  clawTarget = 127;
  delay(500);
  liftTarget = LP_LOW + 200;
  autoDrive(-600);
  drive(-60);
  delay(300);
  armTarget = AP_STACK + 200;
  delay(700);
  armTarget = AP_STACK;
  clawTarget = -127;
  delay(500);
  autoDrive(600);
  delay(500);
}

// control center ===============================================================
void autonomous() {
  gyroReset(gyro);
  liftTarget = analogRead(LIFTPOT); // calibrate the PID starting values
  armTarget = analogRead(ARMPOT);

  //start all tasks
  TaskHandle aHandle = taskRunLoop(armTask, 20); //start arm
  TaskHandle lHandle = taskRunLoop(liftTask, 20); //start lift
  TaskHandle cHandle = taskRunLoop(clawTask, 20); //start claw

  switch(auton){
    case -1:
      //autoRight = true;
      skills();
    case 0:
      autoDrive(300);
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon20();
      break;
    case 3:
      tower();
      break;
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  taskDelete(cHandle);
  motorStopAll();
}
