
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_adc.h"
#include "em_cmu.h"
#include "segmentlcd.h"
#include "rtcdriver.h"
#include "bsp_trace.h"


/** Timer used for bringing the system back to EM0. */
static RTCDRV_TimerID_t xTimerForWakeUp;

/***************************************************************************//**
 * @brief Initialize ADC for temperature sensor readings in single poin
 ******************************************************************************/
void setupSensor(void)
{
  /* Base the ADC configuration on the default setup. */
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;

  /* Initialize timebases */
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(7000000, 0);
  ADC_Init(ADC0, &init);
}

/***************************************************************************//**
 * @brief  Main function
 ******************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* If first word of user data page is non-zero, enable eA Profiler trace */
  BSP_TraceProfilerSetup();

  /* Enable peripheral clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_ADC0, true);

  /* Initialize RTC timer. */
  RTCDRV_Init();
  RTCDRV_AllocateTimer(&xTimerForWakeUp);

  /* Initialize LCD controller without boost */
  SegmentLCD_Init(false);
  SegmentLCD_AllOff();

  /* Setup ADC for sampling internal temperature sensor. */
  setupSensor();

  uint32_t values[8];
  ADC_InitSingle_TypeDef sInit = ADC_INITSINGLE_DEFAULT;
  sInit.reference = adcRefVDD;
  sInit.acqTime = adcAcqTime32;
  char string[8];

  /* Main loop - just read temperature and update LCD */
  while (1) {
	for (int i = 0; i < 8; i++) {
	  // Init ADC0 with Channel i.
	  sInit.input = i;
	  ADC_InitSingle(ADC0, &sInit);

	  // Start an ADC aquisition
	  ADC_Start(ADC0, adcStartSingle);

	  // Wait for the measurement to complete
	  while ( ADC0->STATUS & ADC_STATUS_SINGLEACT);

	  // Get the ADC value
	  values[i] = ADC_DataSingleGet(ADC0);
	}
	snprintf(string, 8, "%4d%4d%%F", (int) values[0], (int) values[1]);

    SegmentLCD_Number(values[0]);
    SegmentLCD_Write(string);

    /* Sleep for 2 seconds in EM 2 */
    RTCDRV_StartTimer(xTimerForWakeUp, rtcdrvTimerTypeOneshot, 2000, NULL, NULL);
    EMU_EnterEM2(true);
  }
}
