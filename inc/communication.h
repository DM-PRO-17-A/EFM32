#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"

// From left to right PC4-PC2
enum STOP_GO {
  STOP = 0x0,
  GO = 0x4000
};

enum SPEEDS {
  ZERO = 0x0,
  FIFTY = 0x4,
  SEVENTY = 0x8,
  HUNDRED = 0xc
};

enum CROSSROAD_DIRECTIONS {
  LEFT = 0x20,
  RIGHT = 0x10,
  UTURN = 0x30,
  FORWARD = 0x0
};

// CROSSROAD: PB7, BUSY: PB8, CROSSROAD_BUSY: PB7 and PB8
enum OUTPUT {CROSSROAD = 0x80, BUSY = 0x100, CROSSROAD_BUSY = 0x180};


void communication_init(void);

void clear_comm_out(int pin);

void set_comm_out(int pin);

int get_speed(void);

int get_direction(void);

int get_start_stop(void);

#endif /* COMMUNICATION_H */


