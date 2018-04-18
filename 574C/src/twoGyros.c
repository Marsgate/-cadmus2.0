#include "main.h"

int gyRead(){
  int gyroVal = (-gyroGet(gyro1) + gyroGet(gyro2))/2;
  return gyroVal;
}

void gyReset(){
  gyroReset(gyro1);
  gyroReset(gyro2);
}
