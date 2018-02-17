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

Encoder encoder_l;
Encoder encoder_r;
Ultrasonic sonar;

//ports
#define DRIVE1  9//Front left
#define DRIVE2 2//Front right
#define DRIVE3  3//Back left
#define DRIVE4  8//Back right
#define BASE1 4//Mobile base middle right
#define BASE2 7//Mobile base middle left

//Sensors

//Ultrasonic
#define ULTRA_O 11
#define ULTRA_Y 12

//Encoders
#define ENC_L1 1
#define ENC_L2 2
#define ENC_R1 3
#define ENC_R2 4

#define BASEPOT 7

#define GYRO 8
int auton;
#endif
