#include "main.h"
#include "base.h"
#include "drive.h"
#include "Gyro.h"
static int baseT;
void baseTask(){
  autobase(baseT);
}

void comp(){
e_reset();
autodrive(25);
gyroturn(-30);
  baseT=1230;
  delay(1000);
  e_reset();
  autodrive(360*3.2);
  baseT=3980;
  delay(1000);
  e_reset();
  autodrive(-360*3.1);
  gyroturn(-50);
  e_reset();
  autodrive(360*-1.2);
  gyroturn(255);
  e_reset();
  autodrive(360*2.5);
  baseT=2330;
  delay(950);
  e_reset();
  autodrive(-360*1.6);
}
void skills(){
  comp();
gyroturn(80);
e_reset();
autodrive(360*.5);
gyroturn(66);
e_reset();
baseT=1230;
delay(500);
autodrive(360*1.65);
baseT=3980;
delay(1000);
gyroturn(160);
e_reset();
autodrive(360*2.7);
baseT=1950;
delay(1050);
e_reset();
autodrive(360*-.5);
gyroturn(-80);
e_reset();
autodrive(360*1.3);
gyroturn(-66);
baseT=1230;
e_reset();
autodrive(360*1.65);
baseT=3980;
delay(1000);
gyroturn(-160);
e_reset();
autodrive(360*2.7);
baseT=1950;
delay(1050);
e_reset();
autodrive(360*-.5);





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
