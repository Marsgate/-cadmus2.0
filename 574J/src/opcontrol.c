#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "arm.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		clawOp();
		pylonOp();
		armOp();
		delay(20);
	}
}
