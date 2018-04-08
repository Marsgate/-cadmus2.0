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
  autoScoop(0);
  sonarDriveDistance(1300); //go get pylon
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
  lift(45); // hold lift up for rest of auton
}

// =====================================================================
void pylon5(){
  pickUp(); //drive to pylon
  coneStack();
  autoDrive(-1100);
  gyTurn(-180);//face the zone
  autoScoop(0);
  autoDrive(-100); // reverse
}


// ======================================================================
void pylon20(){
  pickUp(); //drive to pylon
  coneStack();

  autoDrive(-1600);
  gyTurn(-125);//face the zone
  autoDrive(200);
  gyTurn(-205);

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
  autoDrive(-650);
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
  scoop(-60);
  gyTurn(-172);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-700);
  gyroReset(gyro);
  gyTurn(135);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-300); //reverse


  //3 /////////////////////////////////////////////////////
  //grab
  gyTurn(-170);
  autoScoop(0);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  driveUntil(100);
  scoopTarget = 0;
  driveUntil(700);
  drive(40);
  //drop
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyroReset(gyro);
  autoDrive(-300); //reverse


  //4 /////////////////////////////////////////////////////
  //grab
  gyTurn(89);
  driveUntil(220);
  gyTurn(117);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-1200);
  gyTurn(85);
  autoDrive(-650);
  gyTurn(-5);
  //drop
  scoopTarget = 0;
  drive(127);
  delay(1000);
  drive(0);
  gyroReset(gyro);
  autoDrive(-700);

  //5 //////////////////////////////////////////////////
  //grab
  autoScoop(0);
  gyTurn(-95);
  driveUntil(800);
  gyTurn(-132);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  driveUntil(-1100);
  gyTurn(-320);
  scoopTarget = 0;
  autoDrive(300);
  //drop
  drive(30);
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  gyroReset(gyro);
  autoDrive(-350); //reverse

  //6 //////////////////////////////////////////////////
  //grab
  autoScoop(0);
  gyTurn(-190);
  sonarDrive();
  scoopTarget = 1;
  while(analogRead(SCOOPPOT) < SP_MID) delay(20);
  //alignment
  autoDrive(-700);
  gyTurn(-20);
  //drop
  drive(40);
  manualDrop();
  gyroReset(gyro);
  autoDrive(-500);


  //7 /////////////////////////////////////////////////////////
  //grab
  gyTurn(-170);
  scoopTarget = 0;
  sonarDrive();
  scoopTarget = 1;
  //alignment
  gyroReset(gyro);
  driveUntil(600);
  gyTurn(-20);
  scoopTarget = 0;
  autoDrive(850);
  //drop
  while(analogRead(SCOOPPOT) > SP_MID) delay(20);
  autoDrive(-300); //reverse


  //8 /////////////////////////////////////////////////////////
  //grab
  gyTurn(85);
  driveUntil(500);
  gyTurn(115);
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
  gyroReset(gyro);
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
  autoDrive(5000);
}

// control center ===============================================================
void autonomous() {
  //mutex initialization
  stackMutexInit();

  gyroReset(gyro);
  scoopTarget = 2;

  scHandle = taskRunLoop(scoopTask, 20); //start claw

  switch(auton){
    case -1:
      //autoRight = true;
      skills();
      break;
    case 0:
      autoDrive(1000);
      break; //dont run auton
    case 1:
      pylon5();
      break;
    case 2:
      pylon20();
      break;
    case 3:
      doublePylon();
      break;
    case 4:
      //tower();
      break;
  }

  //stop all tasks
  taskDelete(scHandle);
  motorStopAll();
}
