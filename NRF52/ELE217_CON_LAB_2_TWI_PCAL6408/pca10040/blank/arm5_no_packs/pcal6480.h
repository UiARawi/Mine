




#ifndef INCLUSION_GUARD_PCAL6480_H
#define INCLUSION_GUARD_PCAL6480_H

#include "nrfx_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void twi_init (void);
void Reg_config(void);
uint8_t Read_input_reg(void);
void BUTTON_NUMBER(uint8_t SOME_DATA);
void Turning_led(uint8_t led_bits);
void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
 void gpiote_init(void);
#endif

