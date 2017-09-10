#include "main.h"
#include "ports.h"

void initializeIO() {
  //led port
  pinMode(LED, OUTPUT_OD);
}


void initialize() {
  //sensors
  armEnc = encoderInit(3, 4, false);
  driveEncLeft = encoderInit(D_ENC_L1, D_ENC_L2, false);
  driveEncRight = encoderInit(D_ENC_R1, D_ENC_R2, true);

  //lcd
  lcdInit(uart1);
  lcdClear(uart1);

  //expander light check
	while(analogRead(EXPANDER) < 500){
		digitalWrite(LED, LOW);
		delay(500);
		digitalWrite(LED, HIGH);
		delay(500);
	}

}
