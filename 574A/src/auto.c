#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "gyro.h"


void  DriveTest(){
      autodrive(360*5);
      gyroturn(90);
      e_reset();
      autodrive(360);
    }
void BlueLP5(){

}
void BlueRP5(){

}
void RedLP5(){

}
void RedRP5(){

}
void BlueLP10(){

}
void BlueRP10(){

}
void RedLP10(){

}
void RedRP10(){

}

void CSL(){

}
void CSR(){

}
void CenterPylonR(){

}
void CenterPylonL(){

}

void autonomous() {
  switch(auton){
    case 0:
          break; //dont run auto
    case 1:
        BlueLP5();
          break; // blue left pylon
    case 2:
        BlueRP5(); // blue right pylon
          break;
    case 3:
        RedLP5();
          break; // red left pylon
    case 4:
        RedRP5();
          break; // red right pylon
    case 5:
        BlueLP10();
          break; // blue left pylon
    case 6:
        BlueRP10(); // blue right pylon
          break;
    case 7:
        RedLP10();
          break; // red left pylon
    case 8:
        RedRP10();
          break;
    case 9:
        CSL(); //center stack left
          break;
    case 10:
        CSR(); // center stack right
          break;
    case 11:
        CenterPylonR();
          break;
    case 12:
    CenterPylonL();
    break;
    case  13:
        DriveTest(); // name says it
          break;
  }
}
