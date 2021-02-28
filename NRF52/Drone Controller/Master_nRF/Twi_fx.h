#ifndef TWI_FX_H
#define TWI_FX_H

#include "cmsis_os.h"
#include "nrf_drv_twi.h"
#include "nrfx_gpiote.h"
#include "DEFINES.h"


/* TWI instance. */
//static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
void twi_init (void);
void  SLAVE_Config (uint8_t SlaveAddress, uint8_t RegAddress, uint8_t RegSet );
uint8_t SLAVE_Read (uint8_t SlaveAddress, uint8_t RegAddress );
void twiSetRegisters (void);


#endif
