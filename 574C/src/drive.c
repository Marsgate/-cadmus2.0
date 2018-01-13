#include "main.h"
#include "ports.h"
#include "math.h"

//generic drive functions =============================================
void leftD(int vel){
  motorSet(DRIVEL1, vel);
  motorSet(DRIVEL2, vel);
}
void rightD(int vel){
  motorSet(DRIVER1, vel);
  motorSet(DRIVER2, vel);
}
void drive(int vel){

  int br = 30; // brake

  //velocity normalization
  if(vel > 127) vel = 127 - br;
  if(vel < -127) vel = -127 + br;


  motorSet(DRIVEL1, vel);
  motorSet(DRIVEL2, vel);
  motorSet(DRIVER1, vel);
  motorSet(DRIVER2, vel);
}

// power curve =============================================
void tankSigLPC(){
  double left;
  double right;
  double lJoy = -joystickGetAnalog(1, 3);
  double rJoy = -joystickGetAnalog(1, 2);
  int deadzone = 8;

  if(mode == 4){
    int lnew = -lJoy;
    lJoy = -rJoy;
    rJoy = lnew;
  }

  if(abs(lJoy) > deadzone){
    left = log(256/(lJoy+128)-1)/(-.025);
  }else{
    left = 0;
  }
  if(abs(rJoy) > deadzone){
    right = log(256/(rJoy+128)-1)/(-.025);
  }else{
    right = 0;
  }

  leftD(left);
  rightD(right);
}

// autonomous drive functions =============================================
// forward and backward
void autoDrive(int sp){
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);

  double kp = 0.3;
  int error;
  do{
    int kc = 30;
    int sv = (encoderGet(driveEncLeft) + encoderGet(driveEncRight))/2;

    error = sp-sv;
    if(error < 0) kc = -kc;

    int speed = error*kp + kc;
    drive(speed);

    lcdPrint(uart1, 1, "drive: %d", sv);
    delay(20);
  }while(abs(error) > 5); // deadzone = 10
  drive(0); // stop drive
}


void sonarDrive(){
  drive(127); // start driving forward
  int u; // initialize the container for gyro
  do{
    u = ultrasonicGet(sonar);
    delay(10);
  }while(u > 3 || u < 2); // detect pylon in a certain range
  drive(0); // stop drive
}


void gyTurn(int sp){
  if(autoRight == true) sp = -sp; // inverted turn speed for right auton
  int sv;
  int error;
  double kp = 1.5;

  do{
    int kc = 30;
    sv = gyroGet(gyro);

    error = sp-sv;
    if(error < 0) kc = -kc;

    int ts =  error* kp + kc; // turn speed and PID

    leftD(ts); // set the wheels
    rightD(-ts);

    lcdPrint(uart1, 1, "gy: %d", sv); //print out
    delay(20);
  }while(error != 0);
  drive(0);
}
