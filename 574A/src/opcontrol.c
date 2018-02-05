#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"

void operatorControl() {
	while (1) {
		//lcdSetText(uart1, 1, "    Team 574A");
		lcdPrint(uart1, 1, "Gyro, %d", gyroGet(gyro));
		lcdPrint(uart1, 2, "Basepot, %d", analogRead(BASEPOT));
		driveOp();
		liftOp();
		barOp();
		clawOp();
		pylonOp();
		delay(20);
	}
}
