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
  armTarget = 4095;
  clawTarget = 127; // close claw
  //drive from wall turn
  autoDrive(530); // drive out from wall
  armTarget = AP_AUTO; // raise arm
  gyTurn(40); // turn to face pylon

  //deploy and cone push
  autoScoop(0); // deploy scoop
  autoDrive(1450); // push cones

  //align with pylon and scoop it up
  autoDrive(-400); // reverse from pushed cones
  gyTurn(65); // turn to face pylon
  autoDrive(520); // drive into pylon
  liftTarget = LP_LOW; // move lift to scoring height
  autoScoop(1); // bring scoop up
  armTarget = AP_FRONT; // drop arm to score cone
}

// program 1 ===============================================================
void pylon5() {

  conePushTurn(); //drive to pylon
  gyTurn(55);
  autoDrive(-1100); //reverse to zone
  gyTurn(195);//face the zone

  //release the cone
  clawTarget = -127;
  delay(500);
  armTarget = AP_BOT;

  autoScoop(0);

  //reverse out of zone
  autoDrive(-370);
}


// program 2 ===============================================================
void pylon20(){
  conePushTurn(); //drive to pylon
  gyTurn(58);
  autoDrive(-1990); //reverse to zone
  gyTurn(180); // face the zone
  autoDrive(555); // drive in to the zone
  drive(60);
  delay(200);


  //release the cone
  clawTarget = -127;
  delay(500);
  armTarget = AP_AUTO;

  scoop(-127); //drop pylon scoop
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-785);
}

void skills(){
  pylon20();

  //RED 10 point /////////////////////////////////////////////////////

  //grab the first pylon
  autoScoop(0);
  gyTurn(5);
  autoDrive(600);
  autoScoop(1);

  //face zone
  autoDrive(-700);
  gyTurn(176);
  autoDrive(230);

  //manual drop
  scoop(-127);
  delay(1000);
  scoop(0);

  //reverse out of zone
  autoDrive(-300);


  //BLUE 20 point /////////////////////////////////////////////////////

  // next pylon
  autoScoop(0);
  gyTurn(-6);
  autoScoop(0);
  autoDrive(2300);
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
  autoDrive(650);
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
  autoDrive(2300);
  autoScoop(1);

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
      //autoDrive(1500);
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
  taskDelete(cHandle);
  motorStopAll();
}
