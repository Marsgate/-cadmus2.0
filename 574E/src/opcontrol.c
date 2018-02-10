#include "main.h"
#include "drive.h"
#include "base.h"

void operatorControl() {
	while (1) {
		driveOp();
		baseOp();
		delay(100);
	}
}
