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
  pylon(-127);
  delay(750);
  pylon(0);
  barTarget=2000;
  autodrive(360*1.3);

}

void SWCR(){

}
void SWCB(){

}

void  DriveTest(){
  autodrive(360*4.5);
}
void BlueLP5(){//test me
  pylon(-127);
  delay(750);
  pylon(-25);
  barTarget=2000;
  e_reset();
  autodrive(360*1.5);
  pylon(75);
  delay(1500);
  pylon(0);
  e_reset();
  autodrive(-360*1);
  gyroturn(170);
  e_reset();
  autodrive(360*.5);
  pylon(-127);
  delay(750);
  pylon(0);
  e_reset();
  autodrive(-360*.5);
}
void BlueRP5(){
  e_reset();
  pylon(-127);
  delay(850);
  pylon(-30);
  autodrive(360*2.60);
  e_reset();
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
}

void RedRP5(){//test me

}
void BlueLP10(){//test blp5 then add more final distance
//
}
void BlueRP10(){//test brp5 then add more final distance
  }

void RedLP10(){//test rlp5 then add more final distance

}
void RedRP10(){//test rrp5 then add more final distance
}



void autonomous() {
  barTarget = analogRead(ARMPOT);
  TaskHandle barHandle = taskRunLoop(barTask, 20);

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
        ReleasetheKraken();//unfolds robot and moves forward a little bit
          break;
    case  4:
        DriveTest(); // name says it
          break;
    case 5:
        BlueLP5();
          break; // blue left pylon
    case 6:
        BlueRP5(); // blue right pylon
          break;
    case 7:
        RedLP5();
          break; // red left pylon
    case 8:
        RedRP5();
          break; // red right pylon
    case 9:
        BlueLP10();
          break; // blue left pylon
    case 10:
        BlueRP10(); // blue right pylon
          break;
    case 11:
        RedLP10();
          break; // red left pylon
    case 12:
        RedRP10();
          break;
  }

  taskDelete(barHandle);
}
