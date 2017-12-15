#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		clawOp();
		pylonOp();
		antitipOp();
		delay(20);
	}
}
