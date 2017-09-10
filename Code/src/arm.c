#include "main.h"
#include "ports.h"

void armTest(){
  if(digitalRead(ARM_LIMIT) == LOW){
    encoderReset(armEnc);
  }
}

void arm(int vel){
  motorSet(ARM, vel);
}
