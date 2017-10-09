#include "API.h"
#include "ports.h"

void arcade(){
  int power;
  int turn;
  power = -joystickGetAnalog(1, 3); // vertical axis on left joystick
  turn  = joystickGetAnalog(1, 4); // horizontal axis on left joystick
  motorSet(DRIVEL1, power - turn); // set left wheels
  motorSet(DRIVER1, power + turn); // set right wheels
  motorSet(DRIVER2, power + turn); // set right
}

void tank(){
  int left;
  int right;
  int lJoy;
  int rJoy;
  lJoy = -joystickGetAnalog(1, 3);
  rJoy = -joystickGetAnalog(1, 2);
  left = (-1 * (lJoy*lJoy)/127)+(2*lJoy);
  right = (-1 * (rJoy*rJoy)/127)+(2*rJoy);
  if(lJoy < 0){
    lJoy = abs(lJoy);
    left = (-1 * (lJoy*lJoy)/127)+(2*lJoy);
    left = -left;
  }
  if(rJoy < 0){
    rJoy = abs(rJoy);
    right = (-1 * (rJoy*rJoy)/127)+(2*rJoy);
    right = -right;
  }
  motorSet(DRIVEL1, left);
  motorSet(DRIVER2, right);
  motorSet(DRIVER1, right);
}
