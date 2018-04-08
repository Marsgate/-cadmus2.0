
#include "main.h"
#include "roboControl.h"
#include "lcd.h"

void operatorControl() {
	operatorLCD();

	while (1) {
		// only run the bot when the joystick is connected
		if(isJoystickConnected(1)){
			tankSigLPC();
			clawOp();
			scoopOp();
			armOp();
			liftOp();
		}else{
			//liftPID(LP_LMID);
			if(lcdReadButtons(uart1) == 1){
				gyroReset(gyro);
				encoderReset(driveEncLeft);
				encoderReset(driveEncRight);
			}
		}


		lcdPrint(uart1, 1, "LP: %d", analogRead(LIFTPOT));
		//lcdPrint(uart1, 2, "AP: %d", analogRead(ARMPOT));
		//lcdPrint(uart1, 1, "Gyro: %d", gyroGet(gyro));
		//lcdPrint(uart1, 1, "left: %d", encoderGet(driveEncLeft));
		//lcdPrint(uart1, 2, "right: %d", encoderGet(driveEncRight));
		//lcdPrint(uart1, 2, "Sonar: %d", ultrasonicGet(sonar));
		lcdPrint(uart1, 2, "Scoop: %d", analogRead(SCOOPPOT));

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
