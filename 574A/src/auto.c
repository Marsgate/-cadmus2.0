#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "gyro.h"

static int barTarget;
static int baseTarget;

void barTask(){
  autobar(barTarget);
}
void baseTask(){
  autobase(baseTarget);
}
void ReleasetheKraken(){
  barTarget=1600;//raises arm 65 degrees
  pylon(-127);//lowers MB lift
  delay(750);
  pylon(0);
  autodrive(360*1.3);//drives forward

}

void Tower(){//test me first!!
//delay(2700);
e_reset();
claw(45);
autodrive(-360*1.3);
lift(127);
delay(650);
lift(0);
barTarget=2200;
delay(3000);
delay(750);
claw(-127);
delay(1000);
claw(0);
barTarget=1200;
autodrive(360*.3);
}
void DelayTower(){//test me next
  delay(6000);
  e_reset();
  claw(45);
  autodrive(-360*1.3);
  lift(127);
  delay(650);
  lift(0);
  barTarget=1950;
  delay(3000);
  delay(750);
  claw(-127);
  delay(1000);
  claw(0);
  barTarget=1200;
  autodrive(360*.3);
}

void  DriveTest(){
  autodrive(360*4.5);//Ram
}
void BRL17(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(980);
  pylon(-20);
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  claw(0);
  gyroturn(-190);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*.4);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(1450);
  pylon(0);
  e_reset();
  autodrive(-360*.6);//reverses away from MB then stops

}
void BRR17(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(980);
  pylon(-20);
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  claw(0);
  gyroturn(190);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*.4);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(1450);
  pylon(0);
  e_reset();
  autodrive(-360*.6);//reverses away from MB then stops

}

void BRL27(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(980);
  pylon(-20);
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  claw(0);
  gyroturn(-110);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*1.3);
  gyroturn(-70);
  e_reset();
  autodrive(360*1.2);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(1000);
  pylon(40);
  e_reset();
  autodrive(-360*1.3);//reverses away from MB then stops
}

void BRR27(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  pylon(-127);// lowers MB lift
  delay(980);
  pylon(-20);
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  pylon(75);// picks up MB
  delay(1500);
  pylon(0);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  claw(0);
  gyroturn(110);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*1.3);
  gyroturn(70);
  e_reset();
  autodrive(360*1.2);//drives foreward to 5pt zone
  pylon(-127);//lowers MB
  delay(1000);
  pylon(40);
  e_reset();
  autodrive(-360*1.3);//reverses away from MB then stops
}
void CenterRight(){
claw(25);
barTarget=1300;
autodrive(360*1.3);
gyroturn(55);
autodrive(360*1.6);
gyroturn(-90);
baseTarget=2000;
autodrive(360*1.6);
gyroturn(-25);
autodrive(360);
baseTarget=250;
barTarget=600;
gyroturn(-65);
autodrive(360*1.6);
gyroturn(90);
autodrive(360*1.6);
gyroturn(-59);
claw(-127);
delay(100);
barTarget=1300;
autodrive(360*1.4);
baseTarget=2000;
autodrive(-360);

}
void CenterLeft(){

}
void PreloadRed(){//test
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;
  drive(-40);
  delay(200);
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=250;
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  gyroturn(25);
  barTarget=3100;
  claw(127);
  delay(250);
  claw(20);
  barTarget=700;
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=3100;
  claw(127);
  delay(250);
  claw(20);
  barTarget=800;
  gyroturn(120);
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;
  autodrive(360*1.4);
  baseTarget=1300;
  autodrive(-360*.6);
}
void PreloadBlue(){

}
void Skills(){

}

void autonomous() {
  barTarget = analogRead(ARMPOT);
  TaskHandle barHandle = taskRunLoop(barTask, 20);
  baseTarget = analogRead(BASEPOT);
  TaskHandle baseHandle = taskRunLoop(baseTask, 20);

  switch(auton){
    case 0:
          break; //dont run auto
    case 1:
        Tower();
          break;
    case 2:
        DelayTower();
        break;
    case 3:
        ReleasetheKraken();//unfolds robot and moves forward a little bit
          break;
    case  4:
        DriveTest(); // name says it
          break;
    case 5:
        BRL17();
          break; // blue left pylon
    case 6:
        BRR17(); // blue right pylon
          break;
    case 7:
        BRL27();
          break; // red left pylon
    case 8:
        BRR27();
        break;
    case 9:
        CenterRight();
        break;
    case 10:
        CenterLeft();
        break;
    case 11:
        PreloadRed();
        break;
    case 12:
        Skills();
        break;
    }

  taskDelete(barHandle);
  taskDelete(baseHandle);
}
