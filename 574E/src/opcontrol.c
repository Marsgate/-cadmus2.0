#include "main.h"
#include "drive.h"
#include "base.h"
#include "claw.h"
#include "chain.h"

void operatorControl() {
	while (1) {
		driveOp();
		baseOp();
		clawOp();
		chainOp();
		delay(20);
	}
}
