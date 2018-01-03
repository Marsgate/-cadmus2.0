#include "main.h"
#include "ports.h"

void initializeIO() {
  //led port
  pinMode(LED, OUTPUT_OD);
}


void initialize() {

  setTeamName("574C Centurion");

  //setup sensors
  //drive encoders
  driveEncLeft = encoderInit(D_ENC_L1, D_ENC_L2, true);
  driveEncRight = encoderInit(D_ENC_R1, D_ENC_R2, false);
  //drive
  gyro = gyroInit(GYRO, 0);
  gyroReset(gyro);
  //ultrasonic
  sonar = ultrasonicInit(5, 6);


  //lcd
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);


  //expander light check
	while(analogRead(EXPANDER) < 500){
		digitalWrite(LED, LOW);
		delay(500);
		digitalWrite(LED, HIGH);
		delay(500);
    lcdPrint(uart1, 1, "!Check Pwr Exp!");
	}


  delay(200);

  //mode selector from LCD
  autoRight = false;
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
      case -2:
        lcdSetText(uart1, 2, "Auton Skills");
        break;
      case -1:
        lcdSetText(uart1, 2, "Driver Skills");
        mode = 4;
        break;
      case 0:
        lcdSetText(uart1, 2, "None");
        break;
      case 1:
        lcdSetText(uart1, 2, "Left 5pt");
        break;
      case 2:
        lcdSetText(uart1, 2, "Left 20pt");
        break;
      case 3:
        lcdSetText(uart1, 2, "Right 5pt");
        break;
      case 4:
        lcdSetText(uart1, 2, "Right 20pt");
        break;
      case 5:
        lcdSetText(uart1, 2, "Ram");
      default:
        auton = 0;
    }

    delay(20); //space for lcd to update
  }
}
