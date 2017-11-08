
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
	// only run mode selector if not in competition
	while(isOnline() == false){
		lcdSetText(uart1, 1, "1:Op 3:Auto");

		int but = lcdReadButtons(uart1);

		if(but == 1){
			mode = 0;
			break;
		}else if(but == 4){
			mode = 3;
			break;
		}
		delay(50); //space for lcd to update
	}
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
			scoopOp();
			switch(mode){
				case 0:
					autoStack();
					break;
				case 1:
					autoStack();
					break;
				case 2:
					armPID(75);
					liftOp();
					break;
				case 3:
					while(joystickGetDigital(1, 8, JOY_RIGHT) == false){
						delay(20);
					}
					auton = 1;
					autonomous();
					mode = 0;
					break;
			}
		}else{
			//debug
		}


		armTest(); // arm limit switch reset

		lcdPrint(uart1, 1, "Pot: %d", analogRead(LIFTPOT));
		lcdPrint(uart1, 2, "Mode: %d", mode);
		//lcdPrint(uart1, 2, "SH: %d", stackHeight);
		//lcdPrint(uart1, 1, "Enc: %d", encoderGet(armEnc));
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
