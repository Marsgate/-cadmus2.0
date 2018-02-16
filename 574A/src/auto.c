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
e_reset();
claw(45);
autodrive(-360*1.3);
lift(127);
delay(650);
lift(0);
barTarget=2200;
delay(3000);
claw(-127);
delay(1000);
claw(0);
barTarget=1200;
autodrive(360*.3);
}
void DelayTower(){//test me next
  delay(2700);
  //delay(3300);
  e_reset();
  claw(45);
  autodrive(-360*1.3);
  lift(127);
  delay(650);
  lift(0);
  barTarget=2200;
  delay(3000);
  claw(-127);
  delay(1000);
  claw(0);
  barTarget=1200;
  autodrive(360*.3);
}
void  DriveTest(){
  autodrive(360*4.5);//Ram
}
void BRL17(){//test
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;//base lowerd
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=180;
  delay(1000);
  barTarget= 600;//lowers arm
  claw(0);
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  gyroturn(-190);//turns 170 (to account for drift) left towards 5pt zone
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  delay(500);
  baseTarget=1900;
  delay(850);
  e_reset();
  autodrive(-360*1.3);//reverses away from MB then stops
}
void BRR17(){//test
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=180;
  delay(1000);
  barTarget= 600;//lowers arm
  claw(0);
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  gyroturn(180);//180 degree left turn
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  delay(500);
  baseTarget=1900;//base drop off
  delay(850);
  e_reset();
  autodrive(-360*1.3);//reverses away from MB then stops
}

void BRL27(){//test
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=180;
  delay(1000);
  barTarget= 600;//lowers arm
  claw(0);
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  gyroturn(-130);//110 degree left turn
  e_reset();
  autodrive(360*.85);
  gyroturn(-65);//70 degree right turn
  e_reset();
  autodrive(360*1.4);//drives foreward
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  delay(500);
  baseTarget=1900;//drop off MB
  delay(850);
  e_reset();
  autodrive(-360*1);//reverses away from MB then stops
}

void BRR27(){
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=180;
  delay(1000);
  barTarget= 600;//lowers arm
  claw(0);
  e_reset();
  autodrive(-360*2.3);//drives backward to clear cones
  gyroturn(110);//turns 170 (to account for drift) left towards 5pt zone
  e_reset();
  autodrive(360*1.3);
  gyroturn(70);
  e_reset();
  autodrive(360*1.3);//drives foreward to 5pt zone
  claw(-127);//deposits cone on MB
  delay(450);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  delay(500);
  baseTarget=1900;
  delay(850);
  e_reset();
  autodrive(-360*1.3);//reverses away from MB then stops
}
void CenterRight(){//test
claw(25);
barTarget=1300;
e_reset();
autodrive(360*1.3);
gyroturn(-55);
e_reset();
autodrive(360*1.6);
gyroturn(90);
baseTarget=2000;
e_reset();
autodrive(360*1.6);
gyroturn(25);
e_reset();
autodrive(360);
baseTarget=180;
barTarget=600;
gyroturn(65);
e_reset();
autodrive(360*1.6);
gyroturn(-90);
e_reset();
autodrive(360*1.6);
gyroturn(59);
claw(-127);
delay(100);
barTarget=1300;
e_reset();
autodrive(360*1.4);
baseTarget=2000;
e_reset();
autodrive(-360);

}
void CenterLeft(){

}
void PreloadRed(){//test
  claw(25);//claw hold
  barTarget=1300;// raises arm to rough elevation to hold cone
  baseTarget=2000;//base lift down
  e_reset();
  autodrive(360*2.9);//drives foreward to MB
  baseTarget=180;//base lift up
  delay(500);
  barTarget= 600;//lowers arm
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-25);//keeps spinning to affirm cone release
  barTarget=1300;// raises arm to clear cone
  gyroturn(-35);//35 degree right turn
  barTarget=3100;//height of wall
  claw(127);
  delay(250);
  claw(20);
  barTarget=700;//drop off preload cone 1
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-25);//keeps spinning to affirm cone release
  barTarget=3100;//wall height
  claw(127);
  delay(250);
  claw(20);
  barTarget=800;//drops off preload cone 2
  gyroturn(-120);//120 degree turn right
  e_reset();
  autodrive(360*1.4);
  claw(-127);//deposits cone on MB
  delay(250);
  claw(-50);//keeps spinning to affirm cone release
  barTarget=1300;//release height
  claw(0);
  delay(250);
  baseTarget=1950;//drop off base
  delay(850);
  e_reset();
  autodrive(-360*.6);//reverse
}
void PreloadBlue(){

}
void Skills(){
BRL27();
claw(0);
gyroturn(-90);//90 degree turn right
e_reset();
autodrive(360*.7);//drives past stationary
gyroturn(-54);//90 degree turn right
baseTarget=2000;//base lift down
e_reset();
autodrive(360*.8);//drives into MB2
baseTarget=180;//picks up MB2
delay(500);
gyroturn(164);//180 degree turn left
e_reset();
autodrive(360*1.55);//drives to 10 pt
baseTarget=1950;//drops off MB2 on the right side
delay(850);
e_reset();
autodrive(-360*.4);//reverse away
baseTarget=800;
gyroturn(-156);//180 degree turn right
e_reset();
baseTarget=2000;//base lift down
delay(500);
autodrive(360*2.15);//drive to MB3
baseTarget=180;//pickup MB3
delay(500);
e_reset();
autodrive(360*1.85);//Drive towards opp zone
gyroturn(-80);//90 degree right turn
e_reset();
autodrive(360*.82);//drives in front of zone
gyroturn(85);//90 degree left turn, should be centered
e_reset();
autodrive(360*1.4);//drives into 10pt to drop 20pt
baseTarget=1800;//drops off MB3
delay(850);
e_reset();
autodrive(-360*1);//reverses out
baseTarget=800;//raises lift
gyroturn(-80);//90 degree right turn
e_reset();
autodrive(360*.7);//drives forward past stationary
gyroturn(-60);//90 degree right turn
baseTarget=2000;//base lift down
delay(500);
e_reset();
autodrive(360*.8);//drives into MB4
baseTarget=180;//picks up MB4
delay(500);
gyroturn(175);//180 degree left turn
e_reset();
autodrive(360*2);//drive to 10pt
baseTarget=1950;//dropoff MB4 in 10pt
delay(850);
e_reset();
autodrive(-360*.8);//reverse out of zone
baseTarget=800;//base lift up
gyroturn(-167);//180 degree turn right
e_reset();
baseTarget=2000;//base lift down
autodrive(360*1.9);//drive into MB5
baseTarget=180;//picks up MB5
delay(500);
e_reset();
autodrive(360*2.5);//drives forward
gyroturn(-95);//90 degree right turn
e_reset();
autodrive(360*1.3);//drives in front of goals
gyroturn(90);//90 degree left turn
e_reset();
autodrive(360*.6);//drives to 10pt
baseTarget=1950;//drops off into 10 pt
delay(850);
e_reset();
autodrive(-360*.5);//reverse out of zone
baseTarget=800;//raise lift
gyroturn(90);//90 degree left turn
e_reset();
autodrive(360*.8);//drive forward
gyroturn(37);//35 degree left turn
e_reset();
baseTarget=2000;//base lift down
autodrive(360*2.9);//drive forward to MB6
baseTarget=180;//pick up MB6
delay(500);
e_reset();
autodrive(-360*2.3);//reverse out of cones
gyroturn(180);//180 degree left turn
e_reset();
autodrive(360*.4);//drive into 10pt
baseTarget=1950;//drop off MB6
delay(850);
e_reset();
baseTarget=800;//raise base lift
autodrive(-360*2.9);//reverse to park

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
      PreloadBlue();
        break;
    case 13:
        Skills();
        break;
    }

  taskDelete(barHandle);
  taskDelete(baseHandle);
}
