#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "bsp_trace.h"

#include "efm32gg990f1024.h"
#include "em_chip.h"            // required for CHIP_Init() function

/* Counts 1ms timeTicks */
volatile uint32_t msTicks;

/* Local prototypes */
void Delay(uint32_t dlyTicks);

void SysTick_Handler(void){
  // Increment delay counter
  msTicks++;
}

void Delay(uint32_t dlyTicks){
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}

#define GPIO_E 4                // gpioPortE
#define GPIO_A 0				// gpioPortA
#define AIN1 0                  // AIN1 is connected to PortE pin0
#define AIN2 1					// AIN2 is connected to PortE pin1
#define BIN1 1                  // BIN1 is connected to PortA pin1
#define BIN2 2                  // BIN2 is connected to PortA pin2
#define TOP_VAL_PWM 1000        // sets PWM frequency to 1kHz (1MHz timer clock)
#define TOP_VAL_GP_TIMER 1000   // sets general purpose timer overflow frequency to 1kHz (1MHz timer clock)
#define UPDATE_PERIOD 250       // update compare value and toggle LED1 every 250ms
#define INC_VAL (TOP_VAL_PWM/4) // adjust compare value amount

int max_speed = 1000;

void init_motors(){
/* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
	while (1) ;
  }

  uint16_t compare_val = 0; // Initial PWM duty cycle is 0% (LED0 off)

  CMU->HFRCOCTRL = 0x8;                               // Set High Freq. RC Osc. to 1 MHz and use as system source
  CMU->HFPERCLKEN0 = (1 << 13) | (1 << 8) | (1 << 5); // Enable GPIO, Timer0, and Timer3 peripheral clocks
  GPIO->P[GPIO_E].MODEL = (4 << 0) | (4 << 4) | (4 << 8); // Configure AIN1, AIN2 and PWMA pins as digital outputs (push-pull)
  GPIO->P[GPIO_A].MODEL = (4 << 0) | (4 << 4) | (4 << 8); // Configure AIN1, AIN2 and PWMA pins as digital outputs (push-pull)
  GPIO_PinOutSet(gpioPortE, AIN1);
  GPIO_PinOutClear(gpioPortE, AIN2);
  GPIO_PinOutSet(gpioPortA, BIN1);
  GPIO_PinOutClear(gpioPortA, BIN2);

  TIMER0->TOP = TOP_VAL_PWM;
  TIMER3->TOP = TOP_VAL_PWM;                          // PWM period will be 1ms = 1kHz freq

  TIMER0->CNT = 0;
  TIMER3->CNT = 0;                                    // Start counter at 0 (up-count mode)

  TIMER0->CC[0].CCV = compare_val;
  TIMER0->CC[0].CCVB = compare_val;
  TIMER3->CC[2].CCV = compare_val;                    // Set CC2 compare value (0% duty)
  TIMER3->CC[2].CCVB = compare_val;                   // Set CC2 compare buffer value (0% duty)

  TIMER0->CC[0].CTRL = 0x3;                           // Put Timer3 CC channel 2 in PWM mode
  TIMER0->ROUTE |= (TIMER_ROUTE_CC0PEN | TIMER_ROUTE_LOCATION_LOC1); // Connect Timer0 channel 0 to PA0 (PWMB)
  TIMER3->CC[2].CTRL = 0x3;                           // Put Timer3 CC channel 2 in PWM mode
  TIMER3->ROUTE |= (TIMER_ROUTE_CC2PEN | TIMER_ROUTE_LOCATION_LOC1); // Connect PWM output (timer3, channel 2) to PE2 (PWMA). See EFM32GG990 datasheet for details.

  TIMER0->CTRL = (1 << 6);
  TIMER3->CTRL = (1 << 6);                            // Allow timer to run while in debug mode

  TIMER0->CMD = 0x1;                                  // Start Timer3
  TIMER3->CMD = 0x1;                                  // Start Timer3
}

void motor_on(int speed){
	TIMER0->CC[0].CCVB = speed*100;
	TIMER3->CC[2].CCVB = speed*100;
}

void motor_forward(int speed){
	GPIO_PinOutSet(gpioPortE, AIN1);
	GPIO_PinOutClear(gpioPortE, AIN2);
	GPIO_PinOutSet(gpioPortA, BIN1);
	GPIO_PinOutClear(gpioPortA, BIN2);

	motor_on(speed);
}

void motor_left(int speed){
	GPIO_PinOutClear(gpioPortE, AIN1);
	GPIO_PinOutSet(gpioPortE, AIN2);
	GPIO_PinOutSet(gpioPortA, BIN1);
	GPIO_PinOutClear(gpioPortA, BIN2);
	/*
	GPIO->P[GPIO_E].DOUTSET &= ~(1 << AIN1);            // Turn on AIN1 (PE0)
	GPIO->P[GPIO_E].DOUTSET = (1 << AIN2);
	GPIO->P[GPIO_A].DOUTSET = (1 << BIN1);            // Turn on BIN1 (PE0)
	GPIO->P[GPIO_A].DOUTSET &= ~(1 << BIN2);
	*/

	motor_on(speed);
}

void motor_right(int speed){
	GPIO_PinOutSet(gpioPortE, AIN1);
	GPIO_PinOutClear(gpioPortE, AIN2);
	GPIO_PinOutClear(gpioPortA, BIN1);
	GPIO_PinOutSet(gpioPortA, BIN2);
	/*
	GPIO->P[GPIO_E].DOUTSET = (1 << AIN1);            // Turn on AIN1 (PE0)
	GPIO->P[GPIO_E].DOUTSET &= ~(1 << AIN2);
	GPIO->P[GPIO_A].DOUTSET &= ~(1 << BIN1);            // Turn on BIN1 (PE0)
	GPIO->P[GPIO_A].DOUTSET = (1 << BIN2);
	*/

	motor_on(speed);
}

