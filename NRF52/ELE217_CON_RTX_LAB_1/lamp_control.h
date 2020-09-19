#include "cmsis_os.h"

#ifndef INCLUSION_GUARD_LAMP_CONTROL_H
#define INCLUSION_GUARD_LAMP_CONTROL_H

int LampControlInit(void);
void LampControl (void const *argument);
#define SIGNAL_LAMP_START_BLINKING 0x01 
#define SIGNAL_LAMP_STOP_BLINKING 0x02
#define SIGNAL_ADC_START_MEASURING 0x03 
#define SIGNAL_ADC_STOP_MEASURING 0x04

extern osThreadId Led1_ID, Led2_ID, Led3_ID, Led4_ID;;

#endif 
