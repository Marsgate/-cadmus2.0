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
void conePushTurn(){
  //drive from wall turn
  autoDrive(530); // drive out from wall
  clawTarget = 127; // close claw
  gyTurn(35); // turn to face pylon

  //deploy and cone push
  armTarget = AP_MID; // raise arm
  autoScoop(0); // deploy scoop
  autoDrive(1450); // push cones

  //align with pylon and scoop it up
  autoDrive(-400); // reverse from pushed cones
  gyTurn(52); // turn to face pylon
  autoDrive(490); // drive into pylon
  liftTarget = 2100; // move lift to scoring height
  autoScoop(1); // bring scoop up
  armTarget = AP_FRONT; // drop arm to score cone
}

// program 1 ===============================================================
void pylon5() {

  conePushTurn(); //drive to pylon
  /*
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
  */
}


// program 2 ===============================================================
void pylon20(){
  conePushTurn(); //drive to pylon
  gyTurn(-10);
  autoDrive(-2350); //reverse to zone
  gyTurn(107); // face the zone
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

void skills(){
  pylon20();
  gyTurn(100);
  autoDrive(1700);
}

// testing PID ===============================================================
void driveTest(){
  gyTurn(300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}

void ram(){
  armTarget = 3000;
  autoDrive(5000);
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
    case -2:
      skills();
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
    case 5:
      ram();
      break;
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  taskDelete(cHandle)
  motorStopAll();
}
