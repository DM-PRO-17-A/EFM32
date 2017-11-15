#include "em_cmu.h"
#include "em_gpio.h"

#define GPIO_C 2                // gpioPortE
#define GPIO_A 0				// gpioPortA
#define AIN1 9                  // AIN1 is connected to PortE pin0
#define AIN2 7					// AIN2 is connected to PortE pin1
#define PWMA 13
#define BIN1 10                 // BIN1 is connected to PortA pin1
#define BIN2 11                 // BIN2 is connected to PortA pin2
#define PWMB 8
#define TOP_VAL_PWM 1000        // sets PWM frequency to 1kHz (1MHz timer clock)

int current_speed = 5;

void init_motors(void){

  uint16_t compare_val = 0; // Initial PWM duty cycle is 0%

  // Look into using the external crystal.
  CMU->HFRCOCTRL = 0x8;  // Set High Freq. RC Osc. to 1 MHz and use as system source

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_TIMER1, true);
  CMU_ClockEnable(cmuClock_TIMER2, true);

  GPIO_PinModeSet(gpioPortC, AIN1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, AIN2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, PWMA, gpioModePushPull, 0);

  GPIO_PinModeSet(gpioPortC, BIN1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, BIN2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, PWMB, gpioModePushPull, 0);

  GPIO_PinOutClear(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutClear(gpioPortC, BIN2);

  TIMER1->TOP = TOP_VAL_PWM;
  TIMER2->TOP = TOP_VAL_PWM;                          // PWM period will be 1ms = 1kHz freq

  TIMER1->CNT = 0;
  TIMER2->CNT = 0;                                    // Start counter at 0 (up-count mode)

  TIMER1->CC[0].CCV = compare_val;
  TIMER1->CC[0].CCVB = compare_val;
  TIMER2->CC[0].CCV = compare_val;                    // Set CC0 compare value (0% duty)
  TIMER2->CC[0].CCVB = compare_val;                   // Set CC0 compare buffer value (0% duty)

  TIMER1->CC[0].CTRL = 0x3;                           // Put Timer1 CC channel 0 in PWM mode
  TIMER1->ROUTE |= (TIMER_ROUTE_CC0PEN | TIMER_ROUTE_LOCATION_LOC0); // Connect Timer1 channel 0 to PWMA
  TIMER2->CC[0].CTRL = 0x3;                           // Put Timer2 CC channel 0 in PWM mode
  TIMER2->ROUTE |= (TIMER_ROUTE_CC0PEN | TIMER_ROUTE_LOCATION_LOC2); // Connect Timer2 channel 0 to PWMB

  TIMER1->CTRL = (1 << 6);
  TIMER2->CTRL = (1 << 6);                            // Allow timer to run while in debug mode

  TIMER1->CMD = 0x1;                                  // Start Timer1
  TIMER2->CMD = 0x1;                                  // Start Timer2
}

void motor_on(int speed){
  TIMER1->CC[0].CCVB = speed*100;
  TIMER2->CC[0].CCVB = speed*100;
}

void motor_off(void) {
	TIMER1->CC[0].CCVB = 0;
	TIMER2->CC[0].CCVB = 0;
	GPIO_PinOutClear(gpioPortC, AIN1);
	GPIO_PinOutClear(gpioPortC, AIN2);
	GPIO_PinOutClear(gpioPortC, BIN1);
	GPIO_PinOutClear(gpioPortC, BIN2);
}

void motor_forward(int speed){
  GPIO_PinOutSet(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutSet(gpioPortC, BIN1);
  GPIO_PinOutClear(gpioPortC, BIN2);

  motor_on(speed);
}

void motor_left(int speed){
  GPIO_PinOutClear(gpioPortC, AIN1);
  GPIO_PinOutSet(gpioPortC, AIN2);
  GPIO_PinOutSet(gpioPortC, BIN1);
  GPIO_PinOutClear(gpioPortC, BIN2);

  motor_on(speed);
}

void motor_right(int speed){
  GPIO_PinOutSet(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutSet(gpioPortC, BIN2);

  motor_on(speed);
}
