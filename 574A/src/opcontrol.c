#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		clawOp();
		delay(20);
	}
}
