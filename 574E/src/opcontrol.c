#include "main.h"
#include "drive.h"
#include "base.h"

void operatorControl() {
	while (1) {
		driveOp();
		baseOp();
		//lcdPrint(uart1, 1, "left: %d", encoderGet(encoder_l));
		//lcdPrint(uart1, 2, "right: %d", encoderGet(encoder_r));
	lcdPrint(uart1, 1, "POT: %d", analogRead(BASEPOT));
	lcdPrint(uart1, 2, "Gyro: %d",gyroGet(gyro));
		delay(20);
	}
}
