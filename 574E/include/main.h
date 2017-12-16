
#ifndef MAIN_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define MAIN_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

void autonomous();

void initializeIO();

void initialize();

void operatorControl();

// End C++ export structure
#ifdef __cplusplus
}
#endif

//ports
#define DRIVE1 9 //front left
#define DRIVE2 8 //front right
#define DRIVE3 2 //back left
#define DRIVE4 3 //back right

#define BASE1 5 // base right
#define BASE2 6 // base left

#endif
