#include "communication.h"


void communication_init(void) {
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(gpioPortC, 2, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 3, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 4, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 5, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 14, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 8, gpioModePushPull, 0);
}

void clear_comm_out(int pin) {
  // Clear port according to pin
  GPIO_PortOutClear(gpioPortB, pin);
}

void set_comm_out(int pin) {
  // Set pins corresponding to pin
  GPIO_PortOutSet(gpioPortB, pin);
}

int get_speed(void) {
//  return 100; // test override

  int pins = GPIO_PortInGet(gpioPortC) & 0xc;
  switch (pins) {
    case FIFTY:
      return 20;
    case SEVENTY:
      return 30;
    case HUNDRED:
      return 40;
    default:
      return 0;
  }
}

int get_direction(void) {
  return GPIO_PortInGet(gpioPortC) & 0x30;
}

int get_start_stop(void) {
  return GPIO_PortInGet(gpioPortC) & 0x4000;
}
