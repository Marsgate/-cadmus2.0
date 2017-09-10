#include "API.h"
#include "ports.h"
#include "main.h"



void armTest(){
  if(digitalRead(ARM_LIMIT) == LOW){
    encoderReset(armEnc);
  }
}
