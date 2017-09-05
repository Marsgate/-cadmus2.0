
#include "main.h"
#include "drive.h"
#include "lift.h"
#include "scoop.h"
#include "claw.h"
#include "ports.h"

void ptest(int port){
	motorSet(port, 127);
	delay(100);
	motorSet(port, -127);
	delay(100);
}

void operatorControl() {
	while (1) {
		arcade();
		lift();
		scoop();
		grab();
		arm(joystickGetAnalog(1, 2));
		pclaw();
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
