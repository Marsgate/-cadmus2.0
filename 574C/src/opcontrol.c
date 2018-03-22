
#include "main.h"
#include "drive.h"
#include "lift.h"
#include "scoop.h"
#include "claw.h"
#include "ports.h"
#include "autostack.h"
#include "arm.h"
#include "sensorTargets.h"

// used for driver skills
static bool firstStack = false;
static bool bd = false;

void portTest(){
	int i = 0;
	while(1){
		lcdPrint(uart1, 1, "Port: %d", i);
		motorStopAll();
		if(buttonGetState(LCD_CENT)) motorSet(i, 127);
		if(buttonIsNewPress(LCD_RIGHT)) i++;
		if(buttonIsNewPress(LCD_LEFT)) i--;
		delay(20);
	}
}

void operatorControl() {
	// only run debug in non competition
	lcdClear(uart1);
	while(isOnline() == false){
		float p1 = powerLevelMain();
		float p2 = analogRead(EXPANDER);
		lcdPrint(uart1, 2, "1:%0.01f 2:%0.01f", p1/1000, p2/1000);
		lcdSetText(uart1, 1, "Op ------- Debug");
		if(buttonIsNewPress(LCD_LEFT)) break;
		if(buttonIsNewPress(LCD_RIGHT)){
			portTest();
			break;
		}
		if(buttonGetState(JOY1_8R)) autonomous();
		delay(20);
	}

	while (1) {
		if(auton == -1 && isOnline() == true) mode = 4; //skills

		// only run the bot when the joystick is connected
		if(isJoystickConnected(1)){
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
					armPID(AP_ML);
					break;
				case 2:
					break;
				case 3:
					while(joystickGetDigital(1, 8, JOY_RIGHT) == false);
					autonomous();
					break;
				case 4:
					if(firstStack == false){
						armPID(AP_AUTO);
						lift(-15);
						clawGrip(127);
						if(buttonGetState(JOY1_5D)){
							armPID(AP_FRONT);
							liftPID(LP_LOW+50);
							bd = true;
						}
						if(bd == true && buttonGetState(JOY1_5D) == false) firstStack = true;

					}else{
						autoStack();
						clawOp();
					}
					scoopOp();
					tankSigLPC();
					break;
			}
		}else{
			//liftPID(LP_LMID);

			if(lcdReadButtons(uart1) == 1){
				gyroReset(gyro);
				encoderReset(driveEncLeft);
				encoderReset(driveEncRight);
			}
		}

		lcdPrint(uart1, 1, "LP: %d", analogRead(LIFTPOT));
		lcdPrint(uart1, 2, "AP: %d", analogRead(ARMPOT));
		//lcdPrint(uart1, 2, "CP: %d", analogRead(CLAWPOT));
		//lcdPrint(uart1, 2, "Motor: %d", motorGet(LIFT1));
		//lcdPrint(uart1, 1, "Gyro: %d", gyroGet(gyro));
		//lcdPrint(uart1, 1, "left: %d", encoderGet(driveEncLeft));
		//lcdPrint(uart1, 2, "right: %d", encoderGet(driveEncRight));
		//lcdPrint(uart1, 1, "claw: %d", motorGet(CLAW));
		//lcdPrint(uart1, 2, "Sonar: %d", ultrasonicGet(sonar));
		//lcdPrint(uart1, 2, "Scoop: %d", analogRead(SCOOPPOT));
		//lcdPrint(uart1, 1, "Mode: %d", mode);
		//lcdPrint(uart1, 2, "Lift: %d", motorGet(LIFT));

		delay(20);
	}
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
