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
static int clawTarget = 127;

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
void scoopTask(){
  autoScoop(scoopTarget);
}

//task handles
TaskHandle lHandle;
TaskHandle aHandle;
TaskHandle cHandle;
TaskHandle scHandle;
TaskHandle coneHandle;

//drive to pylon program =======================================
void pickUp(){
  clawTarget = 127; // close claw
  armTarget = AP_AUTO; // raise arm
  liftTarget = LP_BOT;
  scoopTarget = 0; // deploy scoop
  drive(127);
  autoScoop(0);
  sonarDrive(); //go get pylon
  scoopTarget = 1; // raise scoop
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
}

void cd(){
  //cone drop
  liftTarget = LP_BOT;
  armTarget = AP_FRONT;
  delay(400);
  clawTarget = -127; // open claw
  delay(200);
  armTarget = AP_AUTO;
  taskDelete(coneHandle);
}
void coneDropTask(void * parameter){
  cd();
}
void coneDrop(){
   coneHandle = taskCreate(coneDropTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

// =====================================================================
void pylon5(){
  pickUp(); //drive to pylon
  driveUntil(-500);
  coneDrop();
  autoDrive(-300);
  gyTurn(-180);//face the zone
  armTarget = AP_AUTO;
  liftTarget = LP_BOT;
  slant(45);
  autoScoop(0);
  autoDrive(-100); // reverse
}

void multiCone() {
  pickUp(); //drive to pylon
  driveUntil(-500);
  coneDrop();
  autoDrive(-300);

  //cone alignment
  gyTurn(-196);//face the zone
  delay(200);
  armTarget = AP_BOT-200;
  liftTarget = LP_BOT-200;
  delay(1200);
  //cone grab
  autoDrive(-300);
  clawTarget = 127;
  delay(500);
  //cone drop
  liftTarget = LP_BOT-100;
  armTarget = AP_FRONT;
  delay(1100);
  cd();

  gyTurn(-205);
  autoDrive(150);
  slant(50);
  autoScoop(0);
  autoDrive(-400); // reverse
}


// ======================================================================
void pylon20(){
  pickUp(); //drive to pylon

  driveUntil(-600);
  coneDrop();
  autoDrive(-380);
  gyTurn(-124);//face the zone
  autoDrive(160);
  gyTurn(-213);

  //drop
  scoopTarget = 2;
  drive(127);
  scoop(-127);
  delay(1200);
  drive(20);
  delay(200);
  scoop(0);

  //reverse out of zone
  autoDrive(-500);
  scoop(-60);
  gyTurn(-398);
}

// ======================================================================
void doublePylon(){
  pylon5();
  gyroReset(gyro);
  gyTurn(140);
  autoDrive(770);
  autoDrive(-50);
  gyTurn(137);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  autoDrive(-400);
  gyTurn(310);
  scoopTarget = 0;
  autoDrive(500);
  autoDrive(-200);
}


void skills(){
  //1 /////////////////////////////////////////////////////
  pylon20();
  gyroReset(gyro);


  //2 /////////////////////////////////////////////////////
  //grab
  autoScoop(0);
  sonarDrive();
  autoScoop(1);
  //alignment
  autoDrive(-400);
  gyroReset(gyro);
  gyTurn(152);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-300); //reverse


  //3 /////////////////////////////////////////////////////
  //grab
  gyTurn(-160);
  autoScoop(0);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  autoDrive(1000);
  //drop
  leftD(-40);
  rightD(-10);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-150); //reverse


  //4 /////////////////////////////////////////////////////
  //grab
  gyTurn(84);
  autoDrive(170);
  gyTurn(115);
  sonarDrive();
  autoScoop(1);
  //alignment
  autoDrive(-950);
  gyTurn(90);
  autoDrive(-360);
  gyTurn(0);
  autoDrive(270);
  //drop
  drive(127);
  scoopTarget = 0;
  delay(700);
  drive(60);
  delay(200);
  gyroReset(gyro);
  autoDrive(-500);

  //5 //////////////////////////////////////////////////
  //grab
  autoScoop(0);
  gyTurn(-88);
  autoDrive(820);
  gyTurn(-128);
  sonarDrive();
  autoScoop(1);
  //alignment
  autoDrive(-880);
  gyTurn(-105);
  autoDrive(-300);
  gyTurn(-20);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-120); //reverse

  //6 //////////////////////////////////////////////////
  //grab
  gyroReset(gyro);
  autoScoop(0);
  gyTurn(-158);
  sonarDrive();
  autoScoop(1);
  //alignment
  autoDrive(-400);
  gyroReset(gyro);
  gyTurn(150);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-250);


  //7 /////////////////////////////////////////////////////////
  //grab
  gyTurn(-157);
  autoScoop(0);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  autoDrive(1050);
  //drop
  drive(50);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-150); //reverse


  //8 /////////////////////////////////////////////////////////
  //grab
  gyTurn(85);
  autoDrive(230);
  gyTurn(115);
  sonarDrive();
  autoScoop(1);
  //alignment
  autoDrive(-900);
  gyTurn(90);
  autoDrive(-360);
  gyTurn(0);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-150); //reverse

  //park
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
  armTarget = AP_AUTO;
  delay(700);
  liftTarget = LP_HMID;
  delay(500);
  autoDrive(500);
  delay(1000);
  armTarget = AP_FRONT;
  liftTarget = LP_LMID;
  delay(700);
  clawTarget = -127;
  delay(500);
  armTarget = AP_AUTO;
  delay(1000);
  autoDrive(-200);
  liftTarget = LP_BOT;
}

// control center ===============================================================
void autonomous() {
  gyroReset(gyro);
  liftTarget = analogRead(LIFTPOT); // calibrate the PID starting values
  armTarget = analogRead(ARMPOT);
  scoopTarget = 2;

  //start all tasks
  aHandle = taskRunLoop(armTask, 20); //start arm
  lHandle = taskRunLoop(liftTask, 20); //start lift
  cHandle = taskRunLoop(clawTask, 20); //start claw
  scHandle = taskRunLoop(scoopTask, 20); //start claw

  switch(auton){
    case -1:
      //autoRight = true;
      skills();
      break;
    case 0:
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon20();
      break;
    case 3:
      multiCone();
      break;
    case 4:
      doublePylon();
      break;
    case 5:
      tower();
      break;
  }

  //stop all tasks
  taskDelete(lHandle);
  taskDelete(aHandle);
  taskDelete(cHandle);
  taskDelete(scHandle);
  motorStopAll();
}
