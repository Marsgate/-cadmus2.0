
#include "main.h"
#include "drive.h"
#include "lift.h"
#include "scoop.h"
#include "claw.h"
#include "ports.h"
#include "autostack.h"
#include "arm.h"
#include "sensorTargets.h"


void ptest(int port){
	lcdPrint(uart1, 1, "%d", port);
	motorSet(port, 127);
	delay(1000);
	motorSet(port, -127);
	delay(1000);
	motorStop(port);
	delay(1000);
}

void gyTest(){
	if(powerLevelMain() < 100){
		gyroShutdown(gyro);
	}
}

void operatorControl() {

	TaskHandle gyHandle = taskRunLoop(gyTest, 20);

	// only run mode selector if not in competition
	while(isOnline() == false){
		lcdSetText(uart1, 1, "1:Op 3:Debug");

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

			//get the mode from 2nd joy
			if(joystickGetDigital(2, 8, JOY_LEFT)){
				mode = 0;
			}else if(joystickGetDigital(2, 8, JOY_DOWN)){
				mode = 1;
			}else if(joystickGetDigital(2, 8, JOY_RIGHT) || joystickGetDigital(1, 5, JOY_UP)){
				mode = 2;
			}else if (joystickGetDigital(2, 8, JOY_UP)){
				mode = 4;
			}

			//get the mode from 1st joy
			if(joystickGetDigital(1, 8, JOY_LEFT)){
				mode = 0;
			}else if(joystickGetDigital(1, 8, JOY_RIGHT)){
				mode = 1;
			}


			switch(mode){
				case 0:
					tankSigLPC();
					clawOp();
					scoopOp();
					autoStack();
					break;
				case 1:
					tankSigLPC();
					clawOp();
					scoopOp();
					autoStack();
					break;
				case 2:
					armOp();
					liftPID(LP_LMID + 300);
					tankSigLPC();
					clawOp();
					scoopOp();
					break;
				case 3:
					while(joystickGetDigital(1, 8, JOY_RIGHT) == false);
					autonomous();
					break;
				case 4:
					if(joystickGetDigital(1, 5, JOY_DOWN)){
							armPID(AP_FRONT);
							liftPID(LP_LOW);
							clawGrip(-127);
					}else{
						clawGrip(127);
						armPID(AP_AUTO);
					}
					scoopSkills();
					tankSigLPC();
					break;
			}
		}else{
			//armPID(1900);
			//gyTurn(90);
			/*
			for(int i=1; i<=10; i++){
				ptest(i);
			}
			*/

			if(lcdReadButtons(uart1) == 1){
				gyroReset(gyro);
				encoderReset(driveEncLeft);
				encoderReset(driveEncRight);
			}
		}

		//lcdPrint(uart1, 1, "LP: %d", analogRead(LIFTPOT));
		//lcdPrint(uart1, 1, "AP: %d", analogRead(ARMPOT));
		//lcdPrint(uart1, 2, "CP: %d", analogRead(CLAWPOT));
		//lcdPrint(uart1, 2, "Motor: %d", motorGet(LIFT1));
		//lcdPrint(uart1, 1, "Gyro: %d", gyroGet(gyro));
		//lcdPrint(uart1, 1, "left: %d", encoderGet(driveEncLeft));
		//lcdPrint(uart1, 2, "right: %d", encoderGet(driveEncRight));
		//lcdPrint(uart1, 1, "claw: %d", motorGet(CLAW));
		//lcdPrint(uart1, 2, "Sonar: %d", ultrasonicGet(sonar));
		//lcdPrint(uart1, 2, "Scoop: %d", analogRead(SCOOPPOT));
		//lcdPrint(uart1, 1, "Mode: %d", mode);

		delay(20);
	}
	taskDelete(gyHandle); // litterally just deals with a warning message
}

/* precautionary measures
while(574C_Members > 0){
	int distance = findNearestTallObject();
	if(distance <= WALKABLE){
		walk();
		climb();
		jump();
	}else{
		playAudio("pumped_up_kicks.mp3");
	}
}
*/
