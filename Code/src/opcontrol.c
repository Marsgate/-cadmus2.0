
#include "main.h"
#include "drive.h"
#include "lift.h"
#include "scoop.h"

void operatorControl() {
	while (1) {
		arcade();
		lift(joystickGetAnalog(1, 2));
		scoop();
		delay(20);
	}
}
