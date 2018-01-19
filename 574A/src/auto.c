#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "gyro.h"

void ReleasetheKraken(){
  pylon(-127);
  delay(750);
  pylon(0);
  autodrive(360*1.3);
  antitip(127);
  delay(1200);
  antitip(0);
  bar(-127);
  delay(1300);
  bar(0);
}

void SWCR(){delay(1500);
drive(127);
delay(170);
drive(0);
pylon(-127);
delay(750);
pylon(0);
bar(-127);
delay(1700);
bar(0);
claw(127);
delay(450);
claw(15);
bar(127);
delay(650);
bar(0);
lift(127);
delay(1500);
lift(0);
drive(127);
delay(200);
drive(0);
bar(-127);
delay(700);
bar(0);
claw(-127);
delay(450);
claw(0);
bar(70);
delay(700);
bar(0);
gyroturn(-75);
e_reset();
autodrive(500);
}
void SWCB(){
  delay(1500);
  drive(127);
  delay(170);
  drive(0);
  pylon(-127);
  delay(750);
  pylon(0);
  bar(-127);
  delay(1700);
  bar(0);
  claw(127);
  delay(450);
  claw(15);
  bar(127);
  delay(650);
  bar(0);
  lift(127);
  delay(1500);
  lift(0);
  drive(127);
  delay(300);
  drive(0);
  bar(-127);
  delay(700);
  bar(0);
  claw(-127);
  delay(450);
  claw(0);
  bar(70);
  delay(700);
  bar(0);
  gyroturn(75);
  e_reset();
  autodrive(500);
}
void Record(){
  pylon(-127);
  delay(750);
  pylon(0);
  e_reset();
  autodrive(360*.7);
  antitip(127);
  delay(1200);
  antitip(0);
  bar(-127);
  delay(800);
  bar(0);
  pylon(50);
  delay(750);
  pylon(0);
  gyroturn(55);
  autostacko();
}


void  DriveTest(){
  autodrive(360*7);
}
void BlueLP5(){//test me
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  gyroturn(9);
  autodrive(360*1.7);
  e_reset();
  autodrive(-150);
  gyroturn(-26);
  e_reset();
  autodrive(150);
  pylon(50);
  delay(1000);
  pylon(0);
  e_reset();
  autodrive(360*1.7);
  pylon(-127);
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-200);
}
void BlueRP5(){
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*.9);
  gyroturn(-100);
  e_reset();
  autodrive(360*.7);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
}
void RedLP5(){//test me
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*.9);
  gyroturn(130);
  e_reset();
  autodrive(360*.7);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
}
void RedRP5(){//test me
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*1.1);
  gyroturn(-190);
  e_reset();
  autodrive(360*.7);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
}
void BlueLP10(){//test blp5 then add distance
//
}
void BlueRP10(){
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*1.3);
  gyroturn(-150
  );
  e_reset();
  autodrive(360*1.3);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
  }

void RedLP10(){//test rlp5 then add more final distance
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*.9);
  gyroturn(160);
  e_reset();
  autodrive(360*1.8);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
}
void RedRP10(){
  e_reset();
  pylon(-127);
  delay(750);
  pylon(0);
  antitip(127);
  delay(250);
  antitip(0);
  autodrive(360*2.60);
  e_reset();
  drive(-50);
  delay(500);
  drive(0);
  pylon(50);
  delay(2000);
  pylon(0);
  delay(100);
  autodrive(-360*1.1);
  gyroturn(-190);
  e_reset();
  autodrive(360*1.2);
  pylon(-127);
  delay(800);
  pylon(0);
  e_reset();
  autodrive(-200);
}



void autonomous() {
  switch(auton){
    case 0:
          break; //dont run auto
    case 1:
        SWCR(); // run this code with 574c
          break;
    case 2:
        SWCB();
        break;
    case 3:
        Record();
        break;
    case 4:
        ReleasetheKraken();//unfolds robot and moves forward a little bit
          break;
    case  5:
        DriveTest(); // name says it
          break;
    case 6:
        BlueLP5();
          break; // blue left pylon
    case 7:
        BlueRP5(); // blue right pylon
          break;
    case 8:
        RedLP5();
          break; // red left pylon
    case 9:
        RedRP5();
          break; // red right pylon
    case 10:
        BlueLP10();
          break; // blue left pylon
    case 11:
        BlueRP10(); // blue right pylon
          break;
    case 12:
        RedLP10();
          break; // red left pylon
    case 13:
        RedRP10();
          break;
  }
}
