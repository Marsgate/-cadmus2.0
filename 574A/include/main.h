#ifndef MAIN_H_

#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif


void autonomous();

void initializeIO();

void initialize();

void operatorControl();
Gyro gyro;

#ifdef __cplusplus
}
#endif

//lift
#define LIFT 4 //vert lift
#define BAR 7 //chainbar


//drive
#define DRIVE1 3 // right front
#define DRIVE2 2 // left back
#define DRIVE3 9 // left front
#define DRIVE4 8 // right back

//claw
#define CLAW 1 // claw

//pylon
#define PYLON1 5 // right
#define PYLON2 6 // left

int drivemode;
int auton;
int side;
#define GYRO 2
#define R_ENCODER1 1
#define R_ENCODER2 2
#define L_ENCODER1 3
#define L_ENCODER2 4
#define LIFT_ENCODER1 5
#define LIFT_ENCODER2 6
#define ARMPOT 3
#define BASEPOT 4
Encoder l_encoder;
Encoder r_encoder;
Encoder lift_encoder;
#endif
