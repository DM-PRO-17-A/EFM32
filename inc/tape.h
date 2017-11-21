#ifndef TAPE_H_
#define TAPE_H_

#include "em_adc.h" // Add em_adc.c
#include "em_cmu.h" // Add em_cmu.c
#include "em_emu.h" // Add em_emu.c


void sensor_init(void);

uint32_t* get_sensor_values(void);

int detect_crossroad(uint32_t* sensor_values);

int detect_drift(uint32_t* sensor_values);

int detect_road(uint32_t* sensor_values);

#endif /* TAPE_H_ */
