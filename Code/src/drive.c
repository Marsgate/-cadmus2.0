#include "API.h"
#include "ports.h"

void arcade(){
  int power;
  int turn;
  power = -joystickGetAnalog(1, 3); // vertical axis on left joystick
  turn  = joystickGetAnalog(1, 4); // horizontal axis on left joystick
  motorSet(DRIVEL1, power - turn); // set left wheels
  motorSet(DRIVEL2, power + turn); // set left wheels
  motorSet(DRIVER1, power + turn); // set right
}
