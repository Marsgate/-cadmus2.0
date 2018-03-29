#include "main.h"
#include "lcd.h"

void initializeIO() {
  //led port
  pinMode(LED, OUTPUT_OD);
}


void initialize() {

  setTeamName("574C Centurion");

  //setup sensors
  driveEncLeft = encoderInit(D_ENC_L1, D_ENC_L2, false);
  driveEncRight = encoderInit(D_ENC_R1, D_ENC_R2, true);
  gyro = gyroInit(GYRO, 0);
  gyroReset(gyro);
  sonar = ultrasonicInit(ULTRA_Y, ULTRA_O);

  //lcd
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);

  buttonInit();

  //expander light check
	while(analogRead(EXPANDER) < 500){
    lcdSetText(uart1, 1, "!Check Pwr Exp!");
		digitalWrite(LED, LOW);
		delay(500);
		digitalWrite(LED, HIGH);
		delay(500);
	}

  initializationLCD();
}
