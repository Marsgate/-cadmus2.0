
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
		tankHPC();
		scoop();
		clawOp();
		//autoStack();

		lcdPrint(uart1, 1, "Pot: %d", analogRead(LIFTPOT));
		//lcdPrint(uart1, 2, "Int: %d", integral);
		//lcdPrint(uart1, 2, "Enc: %d", encoderGet(armEnc));

		delay(20);
	}
}

/*
while(574C_Members > 0){
	int distance = findNearestTallObject();
	if(distance == walkable){
		walk();
		climb();
		jump();
	}else{
		noose();
	}
}
*/
