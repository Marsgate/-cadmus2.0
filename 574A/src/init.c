

#include "main.h"


void initializeIO() {
}


void initialize() {
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
        lcdSetText(uart1, 2, "None");
        break;
      case 1:
        lcdSetText(uart1, 2, "Left 20pt");
        break;
        case 2:
        lcdSetText(uart1, 2, "CSL");
        break;
        case 3:
        lcdSetText(uart1, 2, "CSR");
        break;
        case 4:
        lcdSetText(uart1, 2, "Right  20pt");
        break;
        case 5:
        lcdSetText(uart1, 2, "Test");
        break;
      default:
        auton = 0;
    }

    delay(20); //space for lcd to update
  }
}
