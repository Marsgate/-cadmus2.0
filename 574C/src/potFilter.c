#include "main.h"

static TaskHandle filterHandle;
#define FSIZE 10
int slot = 0;
int liftData[FSIZE];
int armData[FSIZE];

void filterTask(){
  liftData[slot] = analogRead(LIFTPOT);
  armData[slot] = analogRead(ARMPOT);
  slot++;
  if(slot == FSIZE) slot = 0;
}

void filterInit(){
  for(int i = 0; i < FSIZE; i++){
    liftData[i] = 0;
    armData[i] = 0;
  }
  filterHandle = taskRunLoop(filterTask, 10);
  delay(20);
}

int liftRead(){
  int val = 0;
  for(int i = 0; i < FSIZE; i++){
    val += liftData[i];
  }
  val = val/FSIZE;
  return val;
}

int armRead(){
  int val = 0;
  for(int i = 0; i < FSIZE; i++){
    val += armData[i];
  }
  val = val/FSIZE;
  return val;
}
