#include "tape.h"


ADC_InitSingle_TypeDef sInit = ADC_INITSINGLE_DEFAULT;

void ADC0_IRQHandler(void) {
  // Clears interrupt flag
  ADC_IntClear(ADC0, ADC_IF_SINGLE);
}

void sensor_init(void)
{
  /* Enable peripheral clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_ADC0, true);

  /* Base the ADC configuration on the default setup. */
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;

  /* Initialize timebases */
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(7000000, 0);
  ADC_Init(ADC0, &init);

  /* Setup interrupt generation on completed conversion. */
  ADC_IntEnable(ADC0, ADC_IF_SINGLE);
  NVIC_EnableIRQ(ADC0_IRQn);

  sInit.reference = adcRefVDD;
  sInit.acqTime = adcAcqTime32;
}

uint32_t* get_sensor_values(void) {
  /* Writes the sensor values to sensor_values */

  // Array for sensor reading values.
  static uint32_t sensor_values[8];

  // Loop through the eight sensors on the sensor array
  for (int i = 0; i < 8; i++) {
    // Init ADC0 with Channel i.
    sInit.input = i;
    ADC_InitSingle(ADC0, &sInit);

    // Start an ADC aquisition
    ADC_Start(ADC0, adcStartSingle);

    // Wait for the measurement to complete
//    while ( ADC0->STATUS & ADC_STATUS_SINGLEACT);

    /* Wait in EM1 for ADC to complete */
    EMU_EnterEM1();

    // Get the ADC value
    sensor_values[i] = ADC_DataSingleGet(ADC0);
  }
  return sensor_values;
}

int detect_crossroad(uint32_t* sensor_values) {
  for (int i = 0; i < 8; i++) {
    if (sensor_values[i] < 1000) {
      return false;
    }
  }
  return true;
}

int detect_left_drift(uint32_t* sensor_values) {
  return (sensor_values[0] < 1000) &&
         (sensor_values[1] < 1000) &&
         (sensor_values[3] > 1000) &&
         (sensor_values[4] < 1000) &&
         (sensor_values[5] < 1000) &&
         (sensor_values[6] < 1000) &&
         (sensor_values[7] < 1000);
}

int detect_right_drift(uint32_t* sensor_values) {
  return (sensor_values[7] < 1000) &&
         (sensor_values[6] < 1000) &&
         (sensor_values[4] > 1000) &&
         (sensor_values[3] < 1000) &&
         (sensor_values[2] < 1000) &&
         (sensor_values[1] < 1000) &&
         (sensor_values[0] < 1000);
}

int detect_road(uint32_t* sensor_values) {
  return (sensor_values[0] < 1000) &&
		 (sensor_values[1] < 1000) &&
		 (sensor_values[2] < 1000) &&
		 (sensor_values[3] > 1000) &&
         (sensor_values[4] > 1000) &&
		 (sensor_values[5] < 1000) &&
		 (sensor_values[6] < 1000) &&
		 (sensor_values[7] < 1000);
}
