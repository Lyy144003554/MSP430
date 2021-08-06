#ifndef _motor_h
#define _motor_h
#include <msp430.h>

void motor_IO_int();
void ftont();
void stop();
void turn_L();
void turn_R();
void PWM(int pwm1,int pwm2);


#endif
