#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "chainbar.h"

void operatorControl() {
	while (1) {
		driveOp();
		pylonOp();
		antitipOp();
		
		delay(20);
	}
}
