#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"

void operatorControl() {
	while (1) {
		lcdSetText(uart1, 1, "    Team 574A");
		lcdPrint(uart1, 2, "Armpot, %d", analogRead(ARMPOT));
		driveOp();
		liftOp();
		barOp();
		clawOp();
		pylonOp();
		autoalignp();
		delay(20);
	}
}
