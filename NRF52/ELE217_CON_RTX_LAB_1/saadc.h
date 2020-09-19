#include "cmsis_os.h"
#ifndef INCLUSION_GUARD_SAADC_H
#define INCLUSION_GUARD_SAADC_H

int saadc_main_init(void );
void saadc(void const *msg);

extern osThreadId saadc_id;


#endif 
