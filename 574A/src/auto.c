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
  barTarget=2000;//raises arm vertical
  pylon(-127);//lowers MB lift
  delay(750);
  pylon(0);
  autodrive(360*1.3);//drives forward

}

void SWCR(){//test me first!!
  claw(25);//claw hold
  barTarget=1700;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(750);
  pylon(-25);
  e_reset();
  autodrive(360*1.7);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1700;// raises arm to clear cone
  e_reset();
  autodrive(-360*1.2);//drives backward to clear cones
  claw(0);
  gyroturn(-175);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*.8);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-360*.6);//reverses away from MB then stops

}
void SWCB(){//test me next
  claw(25);//claw hold
  barTarget=1700;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(750);
  pylon(-25);
  e_reset();
  autodrive(360*1.7);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1700;// raises arm to clear cone
  e_reset();
  autodrive(-360*1.2);//drives backward to clear cones
  claw(0);
  gyroturn(175);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*.8);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-360*.6);//reverses away from MB then stops
}

void  DriveTest(){
  autodrive(360*4.5);//Ram
}
void BlueLRedL12(){

}
void BlueRRedR12(){

}

void BlueLRedL17(){
}

void BlueRRedR17(){
}





void autonomous() {
  barTarget = analogRead(ARMPOT);
  TaskHandle barHandle = taskRunLoop(barTask, 20);

  switch(auton){
    case 0:
          break; //dont run auto
    case 1:
        SWCR();
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
        BlueLRedL12();
          break; // blue left pylon
    case 6:
        BlueRRedR12(); // blue right pylon
          break;
    case 7:
        BlueLRedL17();
          break; // red left pylon
    case 8:
        BlueRRedR17();
    }

  taskDelete(barHandle);
}
