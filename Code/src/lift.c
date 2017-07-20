#include "API.h"
#include "ports.h"

void lift(int vel){
  motorSet(lift1, vel);
  motorSet(lift2, vel);
  motorSet(lift3, vel);
  motorSet(lift4, vel);
}
