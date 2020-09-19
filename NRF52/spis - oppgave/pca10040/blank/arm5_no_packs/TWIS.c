
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "TWIS.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


/* TWI instance ID. */
#if TWI0_ENABLED 
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif



#define PCAL6408_INT 17
#ifndef PCAL6804_ADDRESS 
#define PCAL6804_ADDRESS 0X20
#endif
#define PCAL6804_CONFIG_REG 0x03
#define PCAL6804_INPUT_REG 0x00
#define PCAL6804_OUTPUT_REG 0x01
#define PCAL6804_IOpin_SETTING 0x0F
#define PCAL6408_PULL_UP_DOWN_ENABLE_REG_ADD 0x43
#define PCAL6408_PULL_UP_DOWN_ENABLE_REG_DATA 0x00
#define PCAL6408_PULL_UP_DOWN_SELECT_REG_ADD 0x44
#define PCAL6408_PULL_UP_DOWN_SELECT_REG_DATA 0xff
#define PCAL6804_INT_MASK_REG_ADD 0x45
#define PCAL6480_SETTING_INTERRUPT_DATA 0xF0


 uint8_t Data_recieved;
 uint8_t Data_send_to_output;
 uint8_t recieved_data;
/* Indicates if operation on TWI has ended. */
static volatile bool m_rxfer_done = false;
static volatile bool m_txfer_done = false;

/**
 * @brief GPIOTE events handler.
 */
 
void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	
	INT_ON_17= true;
	
}



/**
 * @brief TWI events handler.
 */
void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
    switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
							m_rxfer_done = true;
                
            }else if(p_event->xfer_desc.type == NRF_DRV_TWI_XFER_TX){
						
							m_txfer_done = true;
						}
            
            break;
        default:
            break;
    }
}
/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
/**
 * @brief TWI initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = ARDUINO_SCL_PIN,		// SCL signal pin	27
       .sda                = ARDUINO_SDA_PIN,		// SDA signal pin 26
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = true
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, twi_handler, NULL);
    if(err_code== NRF_SUCCESS)
		{
		nrf_drv_twi_enable(&m_twi);
		NRF_LOG_INFO("TWI INITIALIZED");
		NRF_LOG_FLUSH();
		}
    
}



/**
 * @brief Function for main application entry.
 */
 
 void Reg_config(void)
{
			bool detected_device = false;
			m_txfer_done = false;
			ret_code_t err_code_4;
			uint8_t command_conf[2]={PCAL6804_CONFIG_REG,0x0f};
			err_code_4 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,command_conf, sizeof(command_conf), false);
			if (err_code_4 == NRF_SUCCESS)
			{
			detected_device = true;
			NRF_LOG_INFO("TWI device detected at address 0x%x.", PCAL6804_ADDRESS);
			NRF_LOG_INFO("CONFIGURATION REGISTER HAS BEEN MODIFIED");
			NRF_LOG_FLUSH();
			}
			while (m_txfer_done == false);

			m_txfer_done = false;
			ret_code_t err_code_7;
			uint8_t comm[2]={PCAL6804_INT_MASK_REG_ADD, PCAL6480_SETTING_INTERRUPT_DATA};
			err_code_7 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comm, sizeof(comm), false);
			if (err_code_7 == NRF_SUCCESS)
			{

			NRF_LOG_INFO("INTERRUPT MASK REGISTER HAS BEEN CONFIGUERED");
			NRF_LOG_FLUSH();
			}
			while (m_txfer_done == false);

			if (!detected_device)
			{
			NRF_LOG_INFO("No device was found.");
			}
			NRF_LOG_FLUSH();
}

 void gpiote_init(void){
 	nrfx_err_t nrfx_err; 
	nrfx_gpiote_in_config_t switch_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);  
	switch_config.pull=NRF_GPIO_PIN_PULLUP;
	nrfx_err = nrfx_gpiote_init(); 
	if (nrfx_err != NRF_SUCCESS) {
	NRF_LOG_INFO("GPIOTE NOT INITIALIZED");
	NRF_LOG_FLUSH();
	
	} 
	nrfx_err = nrfx_gpiote_in_init(PCAL6408_INT, &switch_config,SwitchMonitorInterruptCB);
	nrfx_gpiote_in_event_enable(PCAL6408_INT, true);
	
	nrf_gpio_cfg_output(8);
	
 
 }


uint8_t BUTTON_NUMBER_SPI(uint8_t SOME_DATA){
	
	SOME_DATA = ~SOME_DATA;
	
	for(int i = 0; i<4; i++){
		if(CHECK_BIT(SOME_DATA,i)){
			NRF_LOG_INFO("BUTTON %i was pushed ", i+1);
			NRF_LOG_FLUSH();
		}
	}
	return SOME_DATA;
}

uint8_t Read_input_reg(void)
{    	
			m_txfer_done = false;
			ret_code_t err_code_2;
			uint8_t input_add_command[1]={PCAL6804_INPUT_REG};
			err_code_2 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,input_add_command, sizeof(input_add_command), true);
			if (err_code_2 == NRF_SUCCESS)
			{
			NRF_LOG_INFO("Ready to read from input register!");
			NRF_LOG_FLUSH();
			}
			
			else
			{
			NRF_LOG_INFO("TWI is Busy!");
			NRF_LOG_FLUSH();
			}

			while (m_txfer_done == false);
			
			m_rxfer_done = false;
			ret_code_t err_code_0;

			err_code_0 = nrf_drv_twi_rx(&m_twi, PCAL6804_ADDRESS, &recieved_data, 1);
			if(err_code_0 == NRF_SUCCESS){ 
			NRF_LOG_INFO("Reading input register0x%x\n\r",recieved_data);
			NRF_LOG_FLUSH();
			}
			while (m_rxfer_done == false);

			return recieved_data;
}


void Turning_led(uint8_t *led_bits){
				

				uint8_t bit_handler = led_bits[0];
				bit_handler = bit_handler<<4;
				m_txfer_done = false;
				ret_code_t err_code_5;
				uint8_t comm[2]={PCAL6804_OUTPUT_REG,bit_handler };
				err_code_5 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comm, sizeof(comm), true);
				if (err_code_5 == NRF_SUCCESS)
				{
				NRF_LOG_INFO("Turning on Led ");
				NRF_LOG_FLUSH();
				}

				else
				{
				NRF_LOG_INFO("TWI is Busy!");
				NRF_LOG_FLUSH();
				}
//				nrf_delay_ms(50);
				while (m_txfer_done == false);

}




