
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "app_gpiote.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"

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
 #define PCAL6804_ADDRESS 0X20
 #define PCAL6804_CONFIG_REG 0x03
 #define PCAL6804_INPUT_REG 0x00
 #define PCAL6804_OUTPUT_REG 0x01
 #define PCAL6804_IOpin_SETTING 0x0F
 #define PCAL6804_INT_MASK_REG_ADD 0x45
 #define PCAL6480_SETTING_INTERRUPT_DATA 0xF0
 
 #define FF_hex 0xFF
 

 #define UINT_F 0x0F
 #define UINT_E 0x0E
 #define UINT_D 0x0D
 #define UINT_C 0x0C
 #define UINT_B 0x0B
 #define UINT_A 0x0A
 #define UINT_9 0x09
 #define UINT_8 0x08
 #define UINT_7 0x07
 #define UINT_6 0x06
 #define UINT_5 0x05
 #define UINT_4 0x04
 #define UINT_3 0x03
 #define UINT_2 0x02
 #define UINT_1 0x01
 #define UINT_0 0x00
 volatile bool INT_ON_17 = false;
 uint8_t Data_recieved;
 uint8_t Data_send_to_output;
 uint8_t recieved_data;

 
 void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);


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

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    if(err_code== NRF_SUCCESS)
		{
		NRF_LOG_INFO("TWI INITIALIZED");
		}
    nrf_drv_twi_enable(&m_twi);
}



/**
 * @brief Function for main application entry.
 */
 
 void Reg_config(void)
{
			bool detected_device = false;
			
//			ret_code_t err_code_9;
//			uint8_t comman_conf[2]={PCAL6804_OUTPUT_REG,0xff};
//			err_code_9 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comman_conf, sizeof(comman_conf), false);
//			if (err_code_9 == NRF_SUCCESS)
//			{
//			
//			NRF_LOG_INFO("OUT ");
//			
//			}
//			

			ret_code_t err_code_4;
			uint8_t command_conf[2]={PCAL6804_CONFIG_REG,0x0f};
			err_code_4 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,command_conf, sizeof(command_conf), false);
			if (err_code_4 == NRF_SUCCESS)
			{
			detected_device = true;
			NRF_LOG_INFO("TWI device detected at address 0x%x.", PCAL6804_ADDRESS);
			NRF_LOG_INFO("CONFIGURATION REGISTER HAS BEEN MODIFIED");
			}
			ret_code_t err_code_7;
			uint8_t comm[2]={PCAL6804_INT_MASK_REG_ADD, PCAL6480_SETTING_INTERRUPT_DATA};
			err_code_7 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comm, sizeof(comm), false);
			if (err_code_7 == NRF_SUCCESS)
			{

			NRF_LOG_INFO("INTERRUPT MASK REGISTER HAS BEEN CONFIGUERED");
			}
			
//			ret_code_t err_code_8;
//			uint8_t dummy[1]= {PCAL6804_INPUT_REG};
//			err_code_8 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS,dummy,sizeof(dummy),true);
//			if(err_code_8 == NRF_SUCCESS){
//			NRF_LOG_INFO("READY TO READ FROM INPUT REGISTER!");
//			};
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
	
	} 
	nrfx_err = nrfx_gpiote_in_init(PCAL6408_INT, &switch_config,SwitchMonitorInterruptCB);
	nrfx_gpiote_in_event_enable(PCAL6408_INT, true);
 
 }


void BUTTON_NUMBER(uint8_t SOME_DATA){

						switch(SOME_DATA){
						case UINT_1:
							NRF_LOG_INFO("BUTTON 1 : PUSHED");
						break;
						case UINT_2:
							NRF_LOG_INFO("BUTTON 2 : PUSHED");
						break;
						case UINT_3:
							NRF_LOG_INFO("BUTTON 1, 2 :  PUSHED");
						break;
						case UINT_4:
							NRF_LOG_INFO("BUTTON 3 : PUSHED");
						break;
						case UINT_5:
							NRF_LOG_INFO("BUTTON 1, 3 : PUSHED");
						break;
						case UINT_6:
							NRF_LOG_INFO("BUTTON 2, 3 : PUSHED");
						break;
						case UINT_7:
							NRF_LOG_INFO("BUTTON 1,2,3 : PUSHED");
						break;
						case UINT_8:
							NRF_LOG_INFO("BUTTON 4 : PUSHED");
						break;
						case UINT_9:
							NRF_LOG_INFO("BUTTON 1,4 : PUSHED");
						break;
						case UINT_A:
							NRF_LOG_INFO("BUTTON 2,4 : PUSHED");
						break;
						case UINT_B:
							NRF_LOG_INFO("BUTTON 1,2,4 : PUSHED");
						break;
						case UINT_C:
							NRF_LOG_INFO("BUTTON 3,4 : PUSHED");
						break;
						case UINT_D:
							NRF_LOG_INFO("BUTTON 1,2,4 : PUSHED");
						break;
						case UINT_E:
							NRF_LOG_INFO("BUTTON 2,3,4 : PUSHED");
						break;
						case UINT_F:
							NRF_LOG_INFO("BUTTON 1,2,3,4 : PUSHED");
						break;
						default:
						break;
						
					}

}

uint8_t Read_input_reg(void)
{    
	  
			static int count = 0;
			ret_code_t err_code_2;
			uint8_t input_add_command[1]={PCAL6804_INPUT_REG};
			err_code_2 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,input_add_command, sizeof(input_add_command), true);
			if (err_code_2 == NRF_SUCCESS)
			{
			NRF_LOG_INFO("Ready to read from Input register!");
			}

			else
			{
			NRF_LOG_INFO("TWI is Busy!");
			NRF_LOG_FLUSH();
			}
			
			ret_code_t err_code_0;

			if(count != 0){
			err_code_0 = nrf_drv_twi_rx(&m_twi, PCAL6804_ADDRESS, &recieved_data, 1);
			if(err_code_0 == NRF_SUCCESS){ 
			NRF_LOG_INFO("Reading input register0x%x, ID: %i ",recieved_data, count);
			}
			}
			count++;
			NRF_LOG_FLUSH();
			return recieved_data;
}


void Turning_led(uint8_t led_bits){
				ret_code_t err_code_5;
				uint8_t comm[2]={PCAL6804_OUTPUT_REG,led_bits };
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
				


}



void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
	
	INT_ON_17= true;
}
