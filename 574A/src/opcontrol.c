#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"


void operatorControl() {
	while (1) {
		lcdPrint(uart1, 1, "Gyro: %d",gyroGet(gyro));
		

		driveOp();
		liftOp();
		barOp();
		clawOp();
		pylonOp();
		antitipOp();
		autostackOp();
	delay(20);
}
}
