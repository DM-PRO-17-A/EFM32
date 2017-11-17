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
//  motor_forward(50); //test

  uint32_t* sensor_values = get_sensor_values();

  // handle crossroad
  if (detect_crossroad(sensor_values)) {
    next_state = ST_CROSSROAD;
    return;
  }
  // TODO: handle drift
}

void crossroad(void) {
  motor_stop();
  Delay(500);
  switch (get_direction()) {
    case LEFT:
      next_state = ST_TURN_LEFT;
      break;
    case RIGHT:
      next_state = ST_TURN_RIGHT;
      break;
    case U_TURN:
      next_state = ST_U_TURN;
      break;
    case FORWARD:
      motor_forward(get_speed());
//      motor_forward(50); // test
      Delay(500);
      next_state = ST_FORWARD;
      break;
//    default:
//      next_state = ST_FORWARD;
  }
}

void turn_left(void) {
  motor_left();
  next_state = ST_FORWARD;
}

void turn_right(void) {
  motor_right();
  next_state = ST_FORWARD;
}

void uturn(void) {
  motor_u_turn();
  next_state = ST_FORWARD;
}

void test(void) {
  motor_forward(50);
  Delay(2000);

  motor_right();

  motor_left();
}


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  motor_init();

  communication_init();

  sensor_init();

//  // test start
//  GPIO_PinModeSet(gpioPortC, 15, gpioModeInputPull, 1);
//  int button1;
//  // test end

  /* Infinite loop */
  while (1) {

    switch (current_state) {
      case ST_WAIT_FOR_GO:
        wait_for_go();
        break;
      case ST_FORWARD:
        forward();
//        test(); // test
        break;
      case ST_CROSSROAD:
        crossroad();
        break;
      case ST_TURN_LEFT:
        turn_left();
        break;
      case ST_TURN_RIGHT:
        turn_right();
	    break;
      case ST_U_TURN:
        uturn();
        break;
      case ST_STOP:
        motor_stop();
        break;
    }

//    // test start
//    button1 = GPIO_PinInGet(gpioPortC, 15);
//    if (button1 && current_state == ST_WAIT_FOR_GO) {
//      next_state = ST_FORWARD;
//    }
//    // test end

    current_state = next_state;
  }
}
