
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
	while (1) {
		// only run the bot when the joystick is connected
		if(isJoystickConnected(1)){

			//get the mode
			if(joystickGetDigital(2, 8, JOY_LEFT)){
				mode = 0;
			}else if(joystickGetDigital(2, 8, JOY_DOWN)){
				mode = 1;
			}else if(joystickGetDigital(2, 8, JOY_RIGHT)){
				mode = 2;
			}

			tankSigLPC();
			clawOp();
			switch(mode){
				case 0:
					autoStack();
					scoopOp();
					break;
				case 1:
					autoStack();
					break;
				case 2:
					armPID(75);
					liftOp();
					break;
			}
		}else{
			//debug
		}


		armTest(); // arm limit switch reset

		//lcdPrint(uart1, 1, "Pot: %d", analogRead(LIFTPOT));
		//lcdPrint(uart1, 2, "SH: %d", stackHeight);
		lcdPrint(uart1, 1, "Enc: %d", encoderGet(armEnc));
		//lcdPrint(uart1, 2, "Motor: %d", motorGet(LIFT1));


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
