#include "main.h"
#include "base.h"
#include "drive.h"
#include "Gyro.h"
static int baseT;
void baseTask(){
  autobase(baseT);
}

void comp(){
  baseT=2000;
  delay(500);
  autodrive(360*1.5);
  baseT=250;
  autodrive(360-1.2);
  gyroturn(130);
  autodrive(360*.6);
  gyroturn(90);
  autodrive(360*1.4);
  baseT=1900;
  autodrive(-360*1.4);
}
void skills(){
  comp();

}
void autonomous() {
baseT=analogRead(BASEPOT);
TaskHandle basehandle= taskRunLoop(baseTask, 20);
switch(auton){
case 0:
break;
case 1:
comp();
break;
case 2:
skills();
break;
}
taskDelete(basehandle);
      }
