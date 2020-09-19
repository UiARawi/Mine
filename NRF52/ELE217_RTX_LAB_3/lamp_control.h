#include "cmsis_os.h"

#ifndef INCLUSION_GUARD_LAMP_CONTROL_H
#define INCLUSION_GUARD_LAMP_CONTROL_H

int LampControlInit(void);
void LampControl (void const *argument);
#define SIGNAL_LAMP_START_BLINKING 0x01 
#define SIGNAL_LAMP_STOP_BLINKING 0x02

extern osThreadId Led1_ID, Led2_ID, Led3_ID, Led4_ID;;

#endif 
