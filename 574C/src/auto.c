#include "main.h"
#include "roboControl.h"
#include "autoFunctions.h"

void scoopTask(){
  autoScoop(scoopTarget);
}

//task handles
TaskHandle scHandle;

//drive to pylon program =======================================
void pickUp(){
  lift(70);
  scoopTarget = 0; // deploy scoop
  drive(127);
  while(analogRead(SCOOPPOT) > SP_BOT) delay(20);
  sonarDriveDistance(1000); //go get pylon
  lift(0);
  scoopTarget = 1; // raise scoop
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
}

void coneStack3(){
  while(analogRead(SCOOPPOT) < SP_INTAKE) delay(20);
  preloadCode();
  autoDrive(150);
  intake();
  stack(2);
  autoDrive(200);
  intake();
  stack(3);
}

void coneStack4(){
  while(analogRead(SCOOPPOT) < SP_INTAKE) delay(20);
  preloadCode();
  autoDrive(150);
  intake();
  stack(2);
  autoDrive(180);
  intake();
  stack(3);
  autoDrive(170);
  intake();
  stack(4);
}

// =====================================================================
void pylon5(){
  pickUp(); //drive to pylon
  coneStack4();
  autoDrive(-1700);
  gyTurn(-180);//face the zone
  scoopTarget = 0;
  while(analogRead(SCOOPPOT) > SP_BOT) delay(20);
  autoDrive(-200); // reverse
}

void pylon10(){
  pickUp(); //drive to pylon
  coneStack4();
  autoDrive(-1600);
  gyTurn(-180);//face the zone
  scoopTarget = 0;
  slant(30, true);
  delay(1200);
  autoDrive(-300); // reverse
}


// ======================================================================
void pylon20(){
  pickUp(); //drive to pylon
  coneStack3();

  //alignment
  autoDrive(-1500);
  gyTurn(-134);//face the zone
  if(autoRight == true) driveUntil(200); // small adjustment for right side auton
  autoDrive(500);
  gyTurn(-222);

  scoopTarget = 2;
  drive(127);
  delay(800);
  drive(40);
  scoop(-127);
  delay(400);
  drive(0);
  delay(500);
  scoop(0);

  //reverse out of zone
  autoDrive(-600);
}


void skills(){
  //1 /////////////////////////////////////////////////////
  pickUp(); //drive to pylon
  driveUntil(-400);
  preload();
  //alignment
  autoDrive(-900);
  gyTurn(-134);//face the zone
  autoDrive(500);
  gyTurn(-222);
  //fast drop
  scoopTarget = 0;
  drive(127);
  delay(1000);
  drive(0);
  delay(300);
  scoopTarget = -1;
  lift(5);
  //reverse out of zone
  autoDrive(-600);
  gyReset();

  //2 /////////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(-110);
  slant(5, true);
  while(gyRead() >  -167) delay(20);
  sonarDriveDistance(300);
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-550);
  delay(200);
  gyTurn(-44);
  scoopTarget = 0;
  slant(5, false);
  while(gyRead() < -16) delay(20);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-170); //reverse

  //3 /////////////////////////////////////////////////////
  //grab
  gyAlign(-183);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  gyReset();
  slant(30, true);
  while(gyRead() > -15);
  slant(25, false);
  while(gyRead() < -3);
  scoopTarget = 0;
  drive(30);
  //drop
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-300); //reverse

  //4 /////////////////////////////////////////////////////
  //grab
  gyTurn(80);
  autoDrive(170);
  slant(20, false);
  while(gyRead() < 119) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1250);
  delay(200);
  gyTurn(85);
  autoDrive(-630);
  gyTurn(-8);
  driveUntil(100);
  //drop
  scoopTarget = 0;
  drive(127);
  delay(1000);
  scoopTarget = -1;
  gyReset();
  autoDrive(-750);

  //5 //////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyAlign(-113);
  autoDrive(790);
  slant(20, true);
  while(gyRead() > -128);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1500);
  delay(200);
  gyTurn(-95);
  autoDrive(-300);
  gyTurn(0);
  //drop
  scoopTarget = 0;
  drive(30);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-250); //reverse

  //6 //////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(-140);
  slant(-10, true);
  while(gyRead() >  -170) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-550);
  delay(200);
  gyTurn(-48);
  scoopTarget = 0;
  slant(5, false);
  while(gyRead() < -15) delay(20);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-300); //reverse

  //7 /////////////////////////////////////////////////////////
  //grab
  gyAlign(-183);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  gyReset();
  driveUntil(200);
  slant(0, true);
  while(gyRead() > -27);
  scoopTarget = 0;
  slant(15, false);
  while(gyRead() < -3);
  drive(0);
  //drop
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-300); //reverse


  //8 /////////////////////////////////////////////////////////
  //grab
  gyTurn(83);
  autoDrive(200);
  slant(10, false);
  while(gyRead() < 116) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1100);
  delay(200);
  gyTurn(-25);
  scoopTarget = 0;
  driveUntil(100);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  scoopTarget = -1;
  gyReset();
  autoDrive(-300); //reverse

  //park
  gyTurn(-33);
  driveUntil(-1200);
}

// testing PID ===============================================================
void driveTest(){
  gyTurn(300);
  lcdPrint(uart1, 1, "dif: %d", abs(encoderGet(driveEncLeft) - encoderGet(driveEncRight)));
  lcdPrint(uart1, 2, "e %d %d", encoderGet(driveEncLeft), encoderGet(driveEncRight));
}

void ram(){
  drive(127);
  delay(5000);
  drive(0);
}

// control center ===============================================================
void autonomous() {
  //mutex initialization
  stackMutexInit();

  gyReset();
  scoopTarget = 2;
  hasPylon = false;

  scHandle = taskRunLoop(scoopTask, 20); //start claw

  switch(auton){
    case -1:
      skills();
      break;
    case 0:
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon10();
      break;
    case 3:
      pylon20();
      break;
    case 4:
      break;
  }

  //stop all tasks
  taskDelete(scHandle);
  motorStopAll();
}
