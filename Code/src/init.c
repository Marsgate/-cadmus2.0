#include "main.h"
#include "ports.h"

void initializeIO() {
  //led port
  pinMode(LED, OUTPUT_OD);
}


void initialize() {

  //setTeamName("574C Centurion");

  //sensors
  armEnc = encoderInit(3, 4, false);
  driveEncLeft = encoderInit(D_ENC_L1, D_ENC_L2, false);
  driveEncRight = encoderInit(D_ENC_R1, D_ENC_R2, true);

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
	}

  //mode selector from LCD
  while(isOnline()){
    lcdSetText(uart1, 1, "1:None 3:L_py");

    int but = lcdReadButtons(uart1);

    if(but == 1){
      auton = 0;
      break;
    }else if(but == 4){
      auton = 1;
      break;
    }
    delay(50); //space for lcd to update
  }
}
