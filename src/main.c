#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"

enum control_input {LEFT, RIGHT, STOP, UTURN, FORWARD, FIFTY, SEVENTY, HUNDRED};

// CROSSROAD: PB7 High, BUSY: PB8 High.
enum control_output {CROSSROAD = 0x80, BUSY = 0x100, BLANK = 0x180};

#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PB6 7
#define PB7 8


void gpio_init() {
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(gpioPortC, 2, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 3, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 4, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortC, 5, gpioModeInputPull, 0);
  GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortB, 8, gpioModePushPull, 0);
}

void clear_comm_out() {
  // Clear PB7 and PB8
  GPIO_PortOutClear(gpioPortB, BLANK);
}

void set_comm_out(int control_command) {
  // Clear both pins.
  clear_comm_out();
  // Set pins corresponding to control_command
  GPIO_PortOutSet(gpioPortB, control_command);
}


int get_comm_in() {
	return GPIO_PortInGet(gpioPortC);
}

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  gpio_init();

  GPIO_PinModeSet(gpioPortD, 8, gpioModeInputPull, 0);

  int Button3;

  int gpio_in;

  set_comm_out(CROSSROAD);

  /* Infinite loop */
  while (1) {
    Button3 = GPIO_PinInGet(gpioPortD, 8);
    gpio_in = get_comm_in();

    if (Button3 == 1) {
      set_comm_out(BUSY);
    }
  }
}
