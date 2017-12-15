#include "main.h"
#include "drive.h"
#include "lift.h"
#include "claw.h"
#include "pylon.h"
#include "antitip.h"
#include "chainbar.h"
#include "antitipz.h"
#include "pylonz.h"
#include "drivez.h"

void operatorControl() {

				while(1){
					drivezOp();
					pylonzOp();
					
					delay(20);


}
}
