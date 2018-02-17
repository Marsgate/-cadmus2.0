#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
//lcdSetText(uart1, 1, "    Team 574A");
//lcdPrint(uart1, 1, "Gyro, %d", gyroGet(gyro));
//lcdPrint(uart1, 2, "Basepot, %d", analogRead(BASEPOT));
//lcdPrint(uart1, 2, "Armpot, %d", analogRead(ARMPOT));
void operatorControl() {
	while (1) {
		if(drivemode==1){//nonskills
			driveOp();
			liftOp();
			barOp();
			clawOp();
			pylonOp();
		}
		else if(drivemode==2){
			static bool armHold = false;
			pylon2Op();
			drive2Op();
			bar2Op();
			clawOp();
			if(joystickGetDigital(1, 7, JOY_UP)) armHold = true;
			if(armHold == true) autobar(1300);
		}
		delay(20);
	}
}
