#ifndef INCLUSION_GUARD_TWI_H
#define INCLUSION_GUARD_TWI_H

#include "nrfx_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

extern  volatile bool INT_ON_17;
extern  volatile bool INT_FROM_SLAVE;
void twi_init (void);
void Reg_config(void);
uint8_t Read_input_reg(void);
uint8_t BUTTON_NUMBER_SPI(uint8_t SOME_DATA);
void Turning_led(uint8_t *led_bits);
void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void gpiote_init(void);
 
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

#define GPIO_PIN_3     3
#define GPIO_PIN_4     4
#define S_ON     1
#define S_OFF    0

#endif
