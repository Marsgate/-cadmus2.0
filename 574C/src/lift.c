#include "main.h"

void lift(int vel){
  motorSet(LIFT, vel);
}

void liftOp(){
  lift(joystickGetAnalog(2, 3));
}
