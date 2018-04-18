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
  sonarDriveDistance(1100); //go get pylon
  lift(0);
  scoopTarget = 1; // raise scoop
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
}

void coneStack(){
  while(analogRead(SCOOPPOT) < SP_INTAKE) delay(20);
  preload();
  autoDrive(150);
  intake();
  stack(2);
  autoDrive(220);
  intake();
  stack(3);
}

// =====================================================================
void pylon5(){
  pickUp(); //drive to pylon
  coneStack();
  autoDrive(-1100);
  gyTurn(-180);//face the zone
  while(analogRead(SCOOPPOT) > SP_BOT) delay(20);
  autoDrive(-100); // reverse
}


// ======================================================================
void pylon20(){
  pickUp(); //drive to pylon
  driveUntil(-400);
  preload();

  //alignment
  autoDrive(-600);
  gyTurn(-130);//face the zone
  autoDrive(500);
  gyTurn(-220);

  //drop
  scoopTarget = 2;
  claw(80);
  drive(127);
  delay(800);
  drive(40);
  scoop(-127);
  delay(400);
  drive(0);
  delay(500);
  scoop(0);

  //reverse out of zone
  autoDrive(-500);
}


void skills(){
  //1 /////////////////////////////////////////////////////
  pylon20();
  gyReset();

  lift(-1); // hold lift up for rest of auton

  //2 /////////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(-155);
  slant(20, true);
  while(gyRead() > -165) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-500);
  delay(200);
  gyTurn(-13);
  scoopTarget = 0;
  driveUntil(100);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-350); //reverse

  //3 /////////////////////////////////////////////////////
  //grab
  gyTurn(-179);
  gyAlign(-181);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  gyReset();
  driveUntil(550);
  slant(25, true);
  while(gyRead() > -5) delay(20);
  scoopTarget = 0;
  driveUntil(150);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-300); //reverse

  //4 /////////////////////////////////////////////////////
  //grab
  gyTurn(90);
  slant(35, false);
  while(gyRead() < 121) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1300);
  delay(200);
  gyTurn(95);
  autoDrive(-650);
  gyTurn(5);
  driveUntil(100);
  //drop
  scoopTarget = 0;
  drive(127);
  delay(800);
  drive(0);
  gyReset();
  autoDrive(-700);

  //5 //////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(-100);
  autoDrive(400);
  slant(40, true);
  while(gyRead() > -132) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1100);
  delay(200);
  gyTurn(-290);
  autoDrive(300);
  slant(-20, true);
  while(gyRead() > -325) delay(20);
  scoopTarget = 0;
  //drop
  drive(30);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-350); //reverse

  //6 //////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(-155);
  slant(20, true);
  while(gyRead() > -165) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-500);
  delay(200);
  gyTurn(-13);
  scoopTarget = 0;
  driveUntil(100);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-350); //reverse


  //7 /////////////////////////////////////////////////////////
  //grab
  gyTurn(-173);
  gyAlign(-175);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  gyReset();
  driveUntil(550);
  slant(25, true);
  while(gyRead() > -5) delay(20);
  scoopTarget = 0;
  driveUntil(150);
  //drop
  drive(40);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyReset();
  autoDrive(-300); //reverse


  //8 /////////////////////////////////////////////////////////
  //grab
  scoopTarget = 0;
  gyTurn(100);
  autoDrive(400);
  slant(40, false);
  while(gyRead() > 132) delay(20);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1200);
  gyTurn(-70);
  scoopTarget = 0;
  autoDrive(500);
  //drop
  drive(40);
  manualDrop();
  gyReset();
  autoDrive(-300); //reverse

  //park
  driveUntil(-1500);
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
      //autoRight = true;
      skills();
      break;
    case 0:
      hasPylon = true;
      while(1){
        if(buttonGetState(JOY1_8R)){
          gyReset();
          gyTurn(90);
        }
        //lcdPrint(uart1, 1, "encAvg: %d", (encoderGet(driveEncLeft)+encoderGet(driveEncRight))/2);
        lcdPrint(uart1, 1, "gyro: %d", gyRead());
        delay(20);
      }
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon20();
      break;
    case 3:
      break;
    case 4:
      break;
  }

  //stop all tasks
  taskDelete(scHandle);
  motorStopAll();
}
