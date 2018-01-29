#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "gyro.h"

static int barTarget;

void barTask(){
  autobar(barTarget);
}

void ReleasetheKraken(){
  barTarget=1600;//raises arm vertical
  pylon(-127);//lowers MB lift
  delay(750);
  pylon(0);
  autodrive(360*1.3);//drives forward

}

void Tower(){//test me first!!
delay(2700);
e_reset();
claw(45);
autodrive(-360*.83);
lift(127);
delay(650);
lift(0);
barTarget=2150;
delay(3000);

delay(750);
claw(-127);
delay(1000);
claw(0);
barTarget=1200;
autodrive(360*.4);
}
void SWCB(){//test me next
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(750);
  pylon(-12);
  e_reset();
  autodrive(360*3.2);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*1.6);//drives backward to clear cones
  claw(0);
  gyroturn(-165);//turns 170 (to account for drift) right towards 5pt zone
  e_reset();
  autodrive(360*1);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-360*1);//reverses away from MB then stops
}

void  DriveTest(){
  autodrive(360*4.5);//Ram
}
void BRL12(){

}
void BRR12(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(550);
  pylon(-12);
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*3.2);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  claw(0);
  gyroturn(200);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*.4);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-360*.6);//reverses away from MB then stops

}

void BRL17(){

}

void BRR17(){

}





void autonomous() {
  barTarget = analogRead(ARMPOT);
  TaskHandle barHandle = taskRunLoop(barTask, 20);

  switch(auton){
    case 0:
          break; //dont run auto
    case 1:
        Tower();
          break;
    case 2:
        SWCB();
        break;
    case 3:
        ReleasetheKraken();//unfolds robot and moves forward a little bit
          break;
    case  4:
        DriveTest(); // name says it
          break;
    case 5:
        BRL12();
          break; // blue left pylon
    case 6:
        BRR12(); // blue right pylon
          break;
    case 7:
        BRL17();
          break; // red left pylon
    case 8:
        BRR17();
    }

  taskDelete(barHandle);
}
