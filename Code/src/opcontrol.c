
#include "main.h"
#include "drive.h"
#include "lift.h"
#include "scoop.h"
#include "claw.h"
#include "ports.h"
#include "autostack.h"
#include "arm.h"

void ptest(int port){
	motorSet(port, 127);
	delay(100);
	motorSet(port, -127);
	delay(100);
}

void operatorControl() {
	autonomous(); // run dat auto
	while (1) {
		/*
		// only run the bot when the joystick is connected
		if(isJoystickConnected(1)){
			tankHPC();
			scoopOp();
			clawOp();
			autoStack();
		}


		armTest(); // arm limit switch reset

		lcdPrint(uart1, 1, "Pot: %d", analogRead(LIFTPOT));
		lcdPrint(uart1, 2, "SH: %d", stackHeight);
		//lcdPrint(uart1, 2, "Enc: %d", encoderGet(armEnc));
		*/

		delay(20);
	}
}

/* precautionary measures
while(574C_Members > 0){
	int distance = findNearestTallObject();
	if(distance == walkable){
		walk();
		climb();
		jump();
	}else{
		playAudio("pumped_up_kicks.mp3");
	}
}
*/
