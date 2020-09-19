




#ifndef INCLUSION_GUARD_PCAL6480_H
#define INCLUSION_GUARD_PCAL6480_H

#include "nrfx_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

int pcal6408_init(void);
uint8_t Read_input_reg(void);
void Turning_led(uint8_t led_bits);








#endif

