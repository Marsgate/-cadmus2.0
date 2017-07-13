#include "API.h"
#include "ports.h"

void arcade(){
  int power;
  int turn;
  power = joystickGetAnalog(1, 2); // vertical axis on left joystick
  turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
  motorSet(driveL, power + turn); // set left wheels
  motorSet(driveR, power - turn); // set right
}
