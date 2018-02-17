/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"


void initializeIO() {
}


void initialize() {


 //Gyro
gyro = gyroInit(GYRO, 0);
gyroReset(gyro);
  //Ultra Sonic
  sonar = ultrasonicInit(ULTRA_O, ULTRA_Y);
  //Encoders
  encoder_l = encoderInit(ENC_L1, ENC_L2, false);
  encoder_r = encoderInit(ENC_R1, ENC_R2, true);

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
      lcdSetText(uart1, 2, "Comp");
      break;
    case 2:
      lcdSetText(uart1, 2, "Skills");
      break;
      default:
      auton=0;
    }
    delay(20);
  }
}
