#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"


void operatorControl() {
	while (1) {
		lcdPrint(uart1, 1, "Left: %d",encoderGet(l_encoder));
		lcdPrint(uart1, 2, "Right: %d", encoderGet(r_encoder));
		

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
