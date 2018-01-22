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
  armTarget = 4095;
  clawTarget = 127; // close claw
  armTarget = AP_AUTO; // raise arm
  liftTarget = LP_LOW;
  autoScoop(0); // deploy scoop
  sonarDrive(); //go get pylon
  autoScoop(1); // bring scoop up
  armTarget = AP_FRONT; // drop arm to score cone
}

// program 1 ===============================================================
void pylon5() {

  pickUp(); //drive to pylon
  autoDrive(-500);
  gyTurn(170);//face the zone

  //release the cone
  clawTarget = -127;
  delay(500);
  armTarget = AP_BOT;
  autoScoop(0);

  //reverse out of zone
  autoDrive(-450);
}


// program 2 ===============================================================
void pylon20(){
  pickUp(); //drive to pylon
  gyTurn(60);
  autoDrive(-1350); //reverse to zone
  gyTurn(180);//face the zone
  drive(60);
  delay(600);


  //release the cone
  clawTarget = -127;
  delay(200);
  armTarget = AP_AUTO;
  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-585);
}

void skills(){
  pylon20();

  //RED 10 point /////////////////////////////////////////////////////

  //grab the first pylon
  autoScoop(0);
  gyTurn(25);
  sonarDrive();
  autoScoop(1);

  //face zone
  autoDrive(-800);
  gyTurn(176);

  //manual drop
  drive(60);
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-400);


  //BLUE 20 point /////////////////////////////////////////////////////
  // next pylon
  autoScoop(0);
  gyTurn(10);
  autoScoop(0);
  sonarDrive();
  autoScoop(1);

  //turn parallel to zone
  autoDrive(1200);
  gyTurn(-80);
  autoDrive(750);

  //align with zone
  gyTurn(-18);
  autoDrive(555); // drive in to the zone
  drive(60);
  delay(200);

  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-700);



  //BLUE 10 point /////////////////////////////////////////////////////

  // next pylon
  autoScoop(0);
  gyTurn(-185);
  sonarDrive();
  autoScoop(1);

  //face zone
  autoDrive(-600);
  gyTurn(-10);
  autoDrive(320);

  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-275);


  //FINAL 10 /////////////////////////////////////////////////////////
  autoScoop(0);
  gyTurn(-195);
  autoScoop(0);
  sonarDrive();

  //turn parallel to zone
  gyTurn(-210);
  autoDrive(1400);

  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-300);

  //face next pylon
  autoScoop(0);
  gyTurn(-45);
  autoDrive(2000);

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

/*  gyTurn(75);
  delay(500);
  armTarget = AP_BOT;
  liftTarget = LP_BOT;
  delay(500);
  autoDrive(-340);
  clawTarget = 127;
  delay(500);
  armTarget = AP_STACK + 100;
  delay(250);
  liftTarget = LP_LMID;
  delay(500);
  gyTurn(125);
  autoDrive(-500);
  drive(-60);
  delay(500);
  clawTarget = -127;
  delay(500);
  autoDrive(700);
*/
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
      //autoRight = true;
      skills();
    case 0:
      //autoDrive(-500);
      //sonarDrive();
      //gyTurn(-45);


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
      tower();
      break;
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  taskDelete(cHandle);
  motorStopAll();
}
