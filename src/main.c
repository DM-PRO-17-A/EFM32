#include <stdlib.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "em_adc.h"
#include "tape.h"
#include "communication.h"
#include "motor.h"
#include "states.h"


int current_state = ST_WAIT_FOR_GO;
int next_state = ST_WAIT_FOR_GO;



void wait_for_go(void) {
  if (get_start_stop() == GO) {
    next_state = ST_FORWARD;
  }
}

void forward(void) {
  motor_forward(get_speed());
  // TODO: handle drift

}


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  init_motors();

  gpio_init();

//  sensor_init();


  int speed = 0;

  uint32_t* sensor_values;

  /* Infinite loop */
  while (1) {

    switch(current_state) {
      case ST_WAIT_FOR_GO:
        wait_for_go();
        break;
      case ST_FORWARD:
        break;
      case ST_CROSSROAD:
        break;
      case ST_TURNING:
        break;
      case ST_STOP:
        break;
    }

    current_state = next_state;
  }
}
