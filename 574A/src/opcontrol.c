#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"

int button1=0;

void operatorControl() {
	while (1) {
		button1 = joystickGetDigital(1,8,JOY_DOWN);
	if(button1!=1){
			lcdPrint(uart1, 1, "OFF Field");
			driveOp();
			liftOp();
			barOp();
			clawOp();
			pylonOp();
			antitipOp();
			autostackofOp();
			tower();
	}
		button1 = joystickGetDigital(1,8,JOY_DOWN);//preload
	if(button1==1){


			lcdPrint(uart1, 1, "Preload");
			driveOp();
			liftOp();
			barOp();
			clawOp();
			pylonOp();
			antitipOp();
			autostackpOp();
			tower();
	}
	delay(20);
	}
	}
