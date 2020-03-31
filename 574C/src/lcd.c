#include "main.h"

void portTest(){
	int i = 0;
	while(1){
		lcdPrint(uart1, 1, "Port: %d", i);
		motorStopAll();
		if(buttonGetState(LCD_CENT)) motorSet(i, 127);
		if(buttonIsNewPress(LCD_RIGHT)) i++;
		if(buttonIsNewPress(LCD_LEFT)) i--;
		delay(20);
	}
}

void operatorLCD(){
	// only run debug in non competition
	lcdClear(uart1);
	while(isOnline() == false){
		float p1 = powerLevelMain();
		float p2 = analogRead(EXPANDER);
		lcdPrint(uart1, 2, "1:%0.2f 2:%0.2f", p1/1000, p2/1000);
		lcdSetText(uart1, 1, "Op ------- Debug");
		if(buttonIsNewPress(LCD_LEFT)) break;
		if(buttonIsNewPress(LCD_RIGHT)){
			portTest();
			break;
		}
		if(buttonGetState(JOY1_8R)) autonomous();
		delay(20);
	}
}

void initializationLCD(){
	int selected = 0; //layered selection
  while(selected < 2){
    lcdSetText(uart1, 2, "");
    while(selected < 1){
      //logic
      if(buttonIsNewPress(LCD_CENT)){
        selected++;
      }else if(buttonIsNewPress(LCD_LEFT)){
        if(auton > -1)auton--;
      }else if(buttonIsNewPress(LCD_RIGHT)){
        if(auton < 5)auton++;
      }

      //display
      switch(auton){
        case -1:
          lcdSetText(uart1, 1, "Skills");
          break;
        case 0:
          lcdSetText(uart1, 1, "None");
          break;
        case 1:
          lcdSetText(uart1, 1, "5pt");
          break;
        case 2:
          lcdSetText(uart1, 1, "10pt");
          break;
        case 3:
          lcdSetText(uart1, 1, "20pt");
          break;
        case 4:
          lcdSetText(uart1, 1, "Tower");
          break;
      }
      delay(20);
    }
    lcdSetText(uart1, 2, "Left ----- Right");
    if(buttonIsNewPress(LCD_CENT)){
      selected--;
    }else if(buttonIsNewPress(LCD_LEFT)){
      selected++;
      lcdSetText(uart1, 2,"left selected");
    }else if(buttonIsNewPress(LCD_RIGHT)){
      selected++;
      lcdSetText(uart1, 2,"right selected");
      autoRight = true;
    }
    delay(20);
  }
}
