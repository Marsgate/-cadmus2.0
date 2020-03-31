#include "main.h"
#include "roboControl.h"

static int cone;
TaskHandle stackHandle;
TaskHandle preloadHandle;
Mutex stackMutex;

void stackMutexInit(){
  stackMutex = mutexCreate();
}

void intake(){
  mutexTake(stackMutex, 999999);
  autoArm(0);
  claw(127);
  arm(-50);
  lift(-127);
  delay(650);
  claw(40);
  arm(0);
  mutexGive(stackMutex);
}

void preloadCode(){
  lift(-127);
  delay(750);
  claw(-127);
  lift(127);
  delay(200);
  lift(0);
  claw(0);
}

void preloadTask(void * parameter){
  mutexTake(stackMutex, 999999);
  preloadCode();
  mutexGive(stackMutex);
  taskDelete(preloadHandle);
}

void preload(){
  preloadHandle = taskCreate(preloadTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stackTask(void * parameter){
  mutexTake(stackMutex, 999999);
  lift(127);
  delay(50*cone + 300);
  lift(0);
  autoArm(1);
  lift(-127);
  delay(330);
  claw(-127);
  delay(150);
  lift(127);
  delay(180);
  lift(0);
  claw(0);
  mutexGive(stackMutex);
  taskDelete(stackHandle);
}

void stack(int sp){
  cone = sp;
  stackHandle = taskCreate(stackTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
