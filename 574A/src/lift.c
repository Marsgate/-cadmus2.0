#include "main.h"

void lift(int vel){
  motorSet(LIFT1, vel);

}

void liftOp(){
  lift(joystickGetAnalog(1, 2));
}
