#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "drivez.h"
#include "liftz.h"
#include "pylonz.h"
#include "clawz.h"
#include "antitipz.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		barOp();
		clawOp();
		pylonOp();
		antitipOp();
		if(joystickGetDigital(1,8,JOY_RIGHT)){
			while (1) {
				drivezOp();
				liftzOp();
				barzOp();
				clawzOp();
				pylonzOp();
				antitipzOp();
				if (joystickGetDigital(1,8,JOY_LEFT)) {
					break;
				}
				delay(20);
			}
		}
		delay(20);
	}
}
