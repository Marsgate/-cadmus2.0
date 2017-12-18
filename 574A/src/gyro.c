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
      left0(ts);
      right0(-ts);
      dir = 0;
    }else if(gy > deg + deadzone){
      left0(-ts);
      right0(ts);
      dir = 1;
    }else{
      if(dir == 0){
        left0(-5);
        right0(5);
      }else{
        left0(5);
        right0(-5);
      }
      delay(150);
      drive0(0);
      break;
    }
  }
}
