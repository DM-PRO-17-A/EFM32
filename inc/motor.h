#ifndef MOTOR_H
#define MOTOR_H

#include "em_cmu.h" // Add em_cmu.c
#include "em_gpio.h" // Add em_gpio.c
#include "em_emu.h" // Add em_emu.c

#define AIN1 9                  // AIN1 is connected to PC9
#define AIN2 7					// AIN2 is connected to PC7
#define PWMA 13                 // PWMA is connected to PC13
#define BIN1 10                 // BIN1 is connected to PC10
#define BIN2 11                 // BIN2 is connected to PC11
#define PWMB 8                  // PWMB is connected to PC8
#define TOP_VAL_PWM 1000        // sets PWM frequency to 1kHz (1MHz timer clock)


void Delay(uint16_t Delay);

void motor_init(void);

void motor_set_speed(int speed);

void motor_off(void);

void motor_forward(int speed);

void motor_left(int speed, int duration);

void motor_right(int speed, int duration);

#endif /* MOTOR_H */
