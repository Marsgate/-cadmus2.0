#include "API.h"
#include "ports.h"
#include "main.h"

void expTest(){
	while(analogRead(EXPANDER) < 500){
		digitalWrite(LED, LOW);
		delay(500);
		digitalWrite(LED, HIGH);
		delay(500);
	}
}

void armTest(){
  if(digitalRead(ARM_LIMIT) == LOW){
    encoderReset(armEnc);
  }
}
