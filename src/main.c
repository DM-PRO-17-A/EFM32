#include <stdlib.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "tape.h"
#include "communication.h"
#include "motor.h"
#include "states.h"


int current_state = ST_WAIT_FOR_GO;
int next_state = ST_WAIT_FOR_GO;

int drift_error = 0;


void wait_for_go(void) {
  if (get_start_stop() == GO) {
    next_state = ST_FORWARD;
  }
}

void step_forward(void) {
  // Step the robot off the crossroad tape
  clear_comm_out(CROSSROAD); // to pynq crossroad low
  set_comm_out(BUSY); // to pynq busy high

  motor_forward(get_speed(), drift_error);

  uint32_t* sensor_values = get_sensor_values();

  if (detect_road(sensor_values)) {
    clear_comm_out(BUSY); // to pynq busy low
    next_state = ST_FORWARD;
  }
}

void forward(void) {
  motor_forward(get_speed(), drift_error);

  uint32_t* sensor_values = get_sensor_values();

  // handle crossroad
  if (detect_crossroad(sensor_values)) {
    next_state = ST_CROSSROAD;
    return;
  }
  // handle drift
  drift_error = detect_drift(sensor_values);
}



void crossroad(void) {
  motor_stop();
  set_comm_out(CROSSROAD); // to pynq crossroad high
  Delay(500);

  if (get_start_stop() == STOP) {
    next_state = ST_STOP;
    return;
  }

  switch (get_direction()) {
//  switch (U_TURN) { // test override
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
      next_state = ST_STEP_FORWARD;
      break;
    default:
      next_state = ST_STEP_FORWARD;
  }
}

void turn_left(void) {
  clear_comm_out(CROSSROAD); // to pynq crossroad low
  set_comm_out(BUSY); // to pynq busy high
  uint32_t* sensor_values = get_sensor_values();
  motor_left();
  if (detect_road(sensor_values)) {
    motor_stop();
    Delay(500);
    clear_comm_out(BUSY); // to pynq busy low
    next_state = ST_FORWARD;
  }
}

void turn_right(void) {
  clear_comm_out(CROSSROAD); // to pynq crossroad low
  set_comm_out(BUSY); // to pynq busy high
  uint32_t* sensor_values = get_sensor_values();
  motor_right();
  if (detect_road(sensor_values)) {
    motor_stop();
    Delay(500);
    clear_comm_out(BUSY); // to pynq busy low
    next_state = ST_FORWARD;
  }
}

void u_turn(void) {
  clear_comm_out(CROSSROAD); // to pynq crossroad low
  set_comm_out(BUSY); // to pynq busy high
  uint32_t* sensor_values = get_sensor_values();
  motor_u_turn();
  if (detect_road(sensor_values)) {
    motor_stop();
    Delay(500);
    clear_comm_out(BUSY); // to pynq busy low
    next_state = ST_FORWARD;
  }
}

void test() {
	set_comm_out(BUSY);
}

int main(void) {
  /* Chip errata */
  CHIP_Init();

  motor_init();

  communication_init();

  sensor_init();

//  // test override start
//  GPIO_PinModeSet(gpioPortC, 15, gpioModeInputPull, 1);
//  int button1;
//  // test override end

  /* Infinite loop */
  while (1) {

    switch (current_state) {
      case ST_WAIT_FOR_GO:
        wait_for_go();
        break;
      case ST_FORWARD:
        forward();
//        test();
        break;
      case ST_STEP_FORWARD:
        step_forward();
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
        u_turn();
        break;
      case ST_STOP:
        motor_stop();
        break;
    }

//    // test override start
//    button1 = GPIO_PinInGet(gpioPortC, 15);
//    if ((button1 && current_state == ST_WAIT_FOR_GO) || (button1 && current_state == ST_STOP)) {
//      next_state = ST_FORWARD;
//    }
//    // test override end

    current_state = next_state;
  }
}
