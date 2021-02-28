#include "Twi_fx.h"
#include <stdbool.h>
#include <nrfx_gpiote.h>
#include <nrfx_uart.h>
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "DEFINES.h"
#include "print_server.h"

/**
 * @brief TWI initialization.
 */
/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
 
void twi_init (void)
{
		//make a instanse of struct err_code;
    ret_code_t err_code;
		//make a instance of struct twi_config and sett values in struct (configures TWI) 
    const nrf_drv_twi_config_t twi_config = {
			//set clock pin
       .scl                = ARDUINO_SCL_PIN,
			//set data pin
       .sda                = ARDUINO_SDA_PIN,
			//set tx freq
       .frequency          = NRF_DRV_TWI_FREQ_100K,
			//interupt prioritet hos master
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
			// Clear bus during initiation
       .clear_bus_init     = false
    };
		//initiate twi with id.... and check for error code
    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    if(err_code!=NRF_SUCCESS)
			PrintServerPrintf("TWI INIT feiled\n");
		//enabel twi HW
    nrf_drv_twi_enable(&m_twi);
}

void twiSetRegisters (void)
{
		// var to hold sampel
    uint8_t sample_data;
		//settup for inputs and outputs
		SLAVE_Config (PCAL6408_ADDRESS, PCAL6408_CONFIG_REG,PCAL6408_CONFIG_REG_VALUE);
		//settup mask for intrupts low is mask sett
		SLAVE_Config(PCAL6408_ADDRESS,PCAL6408_INT_MASK_REG,PCAL6408_INT_MASK_VALUE);
		//set leds to initial value off
		sample_data=INITIAL_LED_STATE;
		SLAVE_Config(PCAL6408_ADDRESS, PCAL6408_OUTPUT_REG,sample_data);
}

void  SLAVE_Config (uint8_t SlaveAddress, uint8_t RegAddress, uint8_t RegSet )
{
	ret_code_t err_code;
	uint8_t sample_data[2];
	sample_data[0]= RegAddress;
	sample_data[1]=RegSet;

	//ber om å få register for config og prents sample data
	err_code = nrf_drv_twi_tx(&m_twi,SlaveAddress,sample_data,sizeof(sample_data),false);
				if (err_code != NRF_SUCCESS)
           PrintServerPrintf("Slav reg config failed\n");
}

uint8_t SLAVE_Read (uint8_t SlaveAddress, uint8_t RegAddress )
{
	ret_code_t err_code;
	uint8_t sample_data;
	sample_data= RegAddress;
	
	//kaller på slave gpio 
	err_code = nrf_drv_twi_tx(&m_twi,SlaveAddress,&sample_data,sizeof(sample_data), true);
				if (err_code != NRF_SUCCESS)
            PrintServerPrintf("Slav reg config failed\n");
	err_code = nrf_drv_twi_rx(&m_twi,SlaveAddress,&sample_data,sizeof(sample_data));
				if (err_code != NRF_SUCCESS)
            PrintServerPrintf("Slav reg read failed\n");
	return sample_data;
}
