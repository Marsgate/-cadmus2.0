
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
#define DRIVE1  3//front left
#define DRIVE2  6//front right
#define DRIVE3  5//back left
#define DRIVE4  7//back right
#define BASE1 2 // base right
#define BASE2 9// base left

#endif
