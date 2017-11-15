//#include "em_device.h"
//#include "em_chip.h"
//#include "em_adc.h" // Add em_adc.c
//#include "em_cmu.h" // Add em_cmu.c
//#include "em_emu.h" // Add em_emu.c
//
//
//
//
//
//ADC_InitSingle_TypeDef sInit = ADC_INITSINGLE_DEFAULT;
//
///***************************************************************************//**
// * @brief ADC0 interrupt handler. Simply clears interrupt flag.
// ******************************************************************************/
//void ADC0_IRQHandler(void)
//{
//  ADC_IntClear(ADC0, ADC_IF_SINGLE);
//}
//
///***************************************************************************//**
// * @brief Initialize ADC for tape sensor readings.
// ******************************************************************************/
//void sensor_init(void)
//{
//  /* Enable peripheral clocks */
//  CMU_ClockEnable(cmuClock_HFPER, true);
//  CMU_ClockEnable(cmuClock_ADC0, true);
//
//  /* Base the ADC configuration on the default setup. */
//  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
//
//  /* Initialize timebases */
//  init.timebase = ADC_TimebaseCalc(0);
//  init.prescale = ADC_PrescaleCalc(7000000, 0);
//  ADC_Init(ADC0, &init);
//
//  /* Setup interrupt generation on completed conversion. */
//  ADC_IntEnable(ADC0, ADC_IF_SINGLE);
//  NVIC_EnableIRQ(ADC0_IRQn);
//
//  sInit.reference = adcRefVDD;
//  sInit.acqTime = adcAcqTime32;
//}
//
//uint32_t* get_sensor_values(void) {
//  /* Writes the sensor values to sensor_values */
//
//  // Array for sensor reading values.
//  static uint32_t sensor_values[8];
//
//  // Loop through the eight sensors on the sensor array
//  for (int i = 0; i < 8; i++) {
//    // Init ADC0 with Channel i.
//    sInit.input = i;
//    ADC_InitSingle(ADC0, &sInit);
//
//    // Start an ADC aquisition
//    ADC_Start(ADC0, adcStartSingle);
//
//    // Wait for the measurement to complete
////    while ( ADC0->STATUS & ADC_STATUS_SINGLEACT);
//
//    /* Wait in EM1 for ADC to complete */
//    EMU_EnterEM1();
//
//    // Get the ADC value
//    sensor_values[i] = ADC_DataSingleGet(ADC0);
//  }
//  return sensor_values;
//}
//
//int detect_crossroad(uint32_t* sensor_values) {
//  for (int i = 0; i < 8; i++) {
//    if (sensor_values[i] < 1000) {
//      return false;
//    }
//  }
//  return true;
//}
//
//int detect_left_drift(void) {
//  return sensor_values[3] > 1000 && sensor_values[4] < 1000;
//}
//
//int detect_right_drift(void) {
//  return sensor_values[4] > 1000 && sensor_values[3] < 1000;
//}
//
//int detect_road(void) {
//  return sensor_values[3] > 1000 && sensor_values[4] > 1000;
//}
//
////int main(void)
////{
////  /* Chip errata */
////  CHIP_Init();
////
////  /* Setup ADC for sampling tape sensor readings. */
////  sensor_init();
////
////  int crossroad;
////
////  int left_drift;
////  int right_drift;
////
////  int on_road;
////
////  /* Infinite loop */
////  while (1) {
////    get_sensor_values();
////
////    crossroad = detect_crossroad();
////
////    left_drift = detect_left_drift();
////    right_drift = detect_right_drift();
////
////    on_road = detect_road();
////  }
////}
