#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "gyro.h"


void  DriveTest(){
  drive0(127);
  delay(7000);
  drive0(0);
}
void BlueLP(){

}
void BlueRP(){

}
void RedLP(){

}
void RedRP(){

}
void CSL(){

}
void CSR(){

}

void autonomous() {
  switch(auton){
    case 0:
        break; //dont run auto
    case 1:
      BlueLP();
        break;
    case 2:
      BlueRP();
        break;
    case 3:
      RedLP();
        break;
    case 4:
      RedRP();
        break;
    case 5:
      CSL();
        break;
    case 6:
      CSR();
        break;
    case 7:
      DriveTest();
        break;
  }
}
