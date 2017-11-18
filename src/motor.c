#include "motor.h"

int turn_speed_inner = 15;
int turn_speed_outer = 50;
uint16_t turn_duration = 3000;
uint16_t u_turn_duration = 6000;


void mini_delay(uint16_t cycle_delay) {
  /* Reset Timer */
  TIMER0->CNT = 0;
  /* Start TIMER0 */
  TIMER0->CMD = TIMER_CMD_START;
  /* Wait until counter value is over top */
  while(TIMER0->CNT < cycle_delay){
  /* Do nothing, just wait */
  }
  TIMER0->CMD = TIMER_CMD_STOP;
}

void Delay(uint16_t Delay) {
	int magic_number = 15; // Don't ask
  /* adjustment factor for 48MHz oscillator, based on the timing of this whole function with speed optimization on, could probably be done in a prettier way. */
  uint32_t cycle_delay = Delay * 48 * magic_number - 28;
  if (cycle_delay > 65000) {
    int length = cycle_delay / 65000;
    for (int i = 0; i < length; i++) {
      mini_delay(65000);
    }
    mini_delay(cycle_delay % 65000 );
  } else {
    mini_delay(cycle_delay);
  }
}



void motor_init(void) {

  uint16_t compare_val = 0; // Initial PWM duty cycle is 0%

  // Look into using the external crystal.
  CMU->HFRCOCTRL = 0x8;  // Set High Freq. RC Osc. to 1 MHz and use as system source

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_TIMER0, true);
  CMU_ClockEnable(cmuClock_TIMER1, true);
  CMU_ClockEnable(cmuClock_TIMER2, true);

  GPIO_PinModeSet(gpioPortC, AIN1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, AIN2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, PWMA, gpioModePushPull, 0);

  GPIO_PinModeSet(gpioPortC, BIN1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, BIN2, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, PWMB, gpioModePushPull, 0);

//  GPIO_PinOutClear(gpioPortC, AIN1);
//  GPIO_PinOutClear(gpioPortC, AIN2);
//  GPIO_PinOutClear(gpioPortC, BIN1);
//  GPIO_PinOutClear(gpioPortC, BIN2);

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

void motor_set_speed(int left_speed, int right_speed) {
  TIMER1->CC[0].CCVB = left_speed * 10;
  TIMER2->CC[0].CCVB = right_speed * 10;
}

void motor_stop(void) {
  motor_set_speed(0, 0);
  GPIO_PinOutClear(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutClear(gpioPortC, BIN2);
}

void motor_forward(int speed) {
  GPIO_PinOutSet(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutSet(gpioPortC, BIN2);

  motor_set_speed(speed, speed);
}

void motor_left(void) {
  GPIO_PinOutSet(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutSet(gpioPortC, BIN2);

  motor_set_speed(turn_speed_outer, turn_speed_inner);
  Delay(turn_duration);
}

void motor_right(void) {
  GPIO_PinOutSet(gpioPortC, AIN1);
  GPIO_PinOutClear(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutSet(gpioPortC, BIN2);

  motor_set_speed(turn_speed_inner, turn_speed_outer);
  Delay(turn_duration);
}

void motor_u_turn(void) {
  // In place u turn
  GPIO_PinOutClear(gpioPortC, AIN1);
  GPIO_PinOutSet(gpioPortC, AIN2);
  GPIO_PinOutClear(gpioPortC, BIN1);
  GPIO_PinOutSet(gpioPortC, BIN2);

  motor_set_speed(turn_speed_outer, turn_speed_outer);
  Delay(u_turn_duration);
}

void motor_correct_left_drift(int speed) {
  motor_set_speed(speed, speed - 10);
  Delay(500);
}

void motor_correct_right_drift(int speed) {
  motor_set_speed(speed - 10, speed);
}
