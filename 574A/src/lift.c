#include "main.h"

void lift(int vel){
  motorSet(LIFT1, vel);
  motorSet(LIFT2, vel);
  motorSet(LIFT3, vel);
  motorSet(LIFT4, vel);
}

void liftOp(){
  lift(joystickGetAnalog(1, 3));
}
