#include "main.h"


void initializeIO() {
}


void initialize() {
  l_encoder = encoderInit(L_ENCODER1, L_ENCODER2,true);
  r_encoder = encoderInit(R_ENCODER1,R_ENCODER2,false);
  lift_encoder = encoderInit(LIFT_ENCODER1, LIFT_ENCODER2, true);


  gyro = gyroInit(GYRO, 0);
  gyroReset(gyro);
  //lcd init
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);


  //mode selector from LCD
  bool selected = false;
  bool buttonDown = false;
  while(selected == false){
    lcdSetText(uart1, 1, "Autonomous");

    int but = lcdReadButtons(uart1); // get the lcd button
    if(but == 0){
      buttonDown = false;
    }else if(buttonDown == false){
      buttonDown = true;
      switch(but){
        case 1:
          auton--;
          break;
        case 2:
          selected = true;
          lcdSetText(uart1, 1, "Selected");
          break;
        case 4:
          auton++;
          break;
      }
    }

    //display current selection
    switch(auton){
    case 0:
      lcdSetText(uart1, 2, "MISSION ABORT");
      break;
    case 1:
      lcdSetText(uart1, 2, "Tower");
      break;
    case 2:
      lcdSetText(uart1, 2, "DelayTower");
      break;
    case 3:
      lcdSetText(uart1, 2, "ReleasetheKraken");
      break;
    case 4:
      lcdSetText(uart1, 2, "Ram");
      break;
    case 5:
      lcdSetText(uart1, 2, "Left10");
      break;
    case 6:
      lcdSetText(uart1, 2, "Right10");
      break;
    case 7:
      lcdSetText(uart1, 2, "Left20");
      break;
    case 8:
      lcdSetText(uart1, 2, "Right20");
      break;
    case 9:
      lcdSetText(uart1, 2, "CenterRight");
        break;
    case 10:
      lcdSetText(uart1, 2, "CenterLeft");
          break;
    case 11:
      lcdSetText(uart1, 2, "PreloadRed");
            break;
    case 12:
      lcdSetText(uart1, 2, "PreloadBlue");
      break;
      case 13:
      lcdSetText(uart1, 2, "Skills");
      break;
      default:
      auton = 0;
    }

    delay(20); //space for lcd to update
  }
}
