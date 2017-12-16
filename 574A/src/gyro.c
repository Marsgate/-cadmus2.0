#include "main.h"
#include "drive.h"
static int dir;

void gyroturn(int deg ){
  int deadzone = 1;
  gyroReset(gyro);
  int ts = 60; // defualt turn speed

  while(1){
    int gy = gyroGet(gyro);
    if(gy < deg - deadzone){
      left(ts);
      right(-ts);
      dir = 0;
    }else if(gy > deg + deadzone){
      left(-ts);
      right(ts);
      dir = 1;
    }else{
      if(dir == 0){
        left(-5);
        right(5);
      }else{
        left(5);
        right(-5);
      }
      delay(150);
      drive(0);
      break;
    }
  }
}
