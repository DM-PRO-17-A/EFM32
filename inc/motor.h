#ifndef MOTOR_H_
#define MOTOR_H_

#include "em_cmu.h" // Add em_cmu.c
#include "em_gpio.h" // Add em_gpio.c
#include "em_emu.h" // Add em_emu.c

#define AIN1 9                // AIN1 is connected to PC9. LEFT
#define AIN2 7	              // AIN2 is connected to PC7. LEFT
#define PWMA 13               // PWMA is connected to PC13. LEFT
#define BIN1 10               // BIN1 is connected to PC10. RIGHT
#define BIN2 11               // BIN2 is connected to PC11. RIGHT
#define PWMB 8                // PWMB is connected to PC8. RIGHT
#define TOP_VAL_PWM 1000      // sets PWM frequency to 1kHz (1MHz timer clock)


void Delay(uint16_t Delay);

void motor_init(void);

void motor_set_speed(int left_speed, int right_speed);

void motor_stop(void);

void motor_forward(int speed, int drift_error);

void motor_left(void);

void motor_right(void);

void motor_u_turn(void);

#endif /* MOTOR_H_ */
