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
  while(analogRead(LIFTPOT) > LP_BOT) lift(-127);
  delay(450);
  claw(40);
  arm(0);
  mutexGive(stackMutex);
}

void preloadTask(void * parameter){
  mutexTake(stackMutex, 999999);
  lift(-127);
  delay(650);
  claw(-127);
  lift(127);
  delay(200);
  lift(0);
  claw(-40);
  mutexGive(stackMutex);
  taskDelete(preloadHandle);
}

void preload(){
  preloadHandle = taskCreate(preloadTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stackTask(void * parameter){
  mutexTake(stackMutex, 999999);
  int target = 200*cone + 600;
  while(analogRead(LIFTPOT) < target-200) liftPID(target);
  autoArm(1);
  lift(-127);
  delay(250);
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
