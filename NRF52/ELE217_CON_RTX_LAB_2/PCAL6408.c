
#include "cmsis_os.h"  
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "app_gpiote.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "print_server.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "switch_monitor.h"


/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

#define UINT_F0 0xF0
#define UINT_F1 0xF1
#define UINT_F2 0xF2
#define UINT_F3 0xF3
#define UINT_F4 0xF4
#define UINT_F5 0xF5
#define UINT_F6 0xF6
#define UINT_F7 0xF7
#define UINT_F8 0xF8
#define UINT_F9 0xF9
#define UINT_FA 0xFA
#define UINT_FB 0xFB
#define UINT_FC 0xFC
#define UINT_FD 0xFD
#define UINT_FE 0xFE


#define PCAL6804_ADDRESS 0X20
#define PCAL6804_CONFIG_REG 0x03
#define PCAL6804_INPUT_REG 0x00
#define PCAL6804_OUTPUT_REG 0x01
#define PCAL6804_IOpin_SETTING 0x0F
#define PCAL6804_INT_MASK_REG_ADD 0x45
#define PCAL6480_SETTING_INTERRUPT_DATA 0xF0

//bool button_1_pushed= false;
//bool button_2_pushed= false;
//bool button_3_pushed= false;
//bool button_4_pushed= false;


uint8_t Data_recieved;
uint8_t Data_send_to_output;
 
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
			PrintServerPrintf("TWI INITIALIZED\n\r");
		}
    nrf_drv_twi_enable(&m_twi);
}

/**
 * @brief Function for main application entry.
 */
 
 void Reg_config(void)
{			
			
			bool detected_device = false;	

			ret_code_t err_code_4;
			uint8_t command_conf[2]={PCAL6804_CONFIG_REG,0x0f};
			err_code_4 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,command_conf, sizeof(command_conf), false);
			if (err_code_4 == NRF_SUCCESS)
			{
			detected_device = true;
			PrintServerPrintf("CONFIGURATION REGISTER IS MODIFIED\n\r");
			PrintServerPrintf("DEVICE DETECTED ON 0X%X:\n\r", PCAL6804_ADDRESS);
			}
			
			ret_code_t err_code_7;
			uint8_t comm[2]={PCAL6804_INT_MASK_REG_ADD, PCAL6480_SETTING_INTERRUPT_DATA};
			err_code_7 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comm, sizeof(comm), false);
			if (err_code_7 == NRF_SUCCESS)
			{
				PrintServerPrintf("INTERRUPT MASK REGISTER IS MODIFIED\n\r");
			}
			if (!detected_device)
			{
				PrintServerPrintf("DEVICE NOT DETECTED\n\r");
			}
			
}

uint8_t Read_input_reg(void)
{    				
						uint8_t recieved_data;
						ret_code_t err_code_2;
						uint8_t input_add_command[1]={PCAL6804_INPUT_REG};
						err_code_2 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,input_add_command, sizeof(input_add_command), true);
						ret_code_t err_code_0;
						err_code_0 = nrf_drv_twi_rx(&m_twi, PCAL6804_ADDRESS, &recieved_data, 1);
						return recieved_data;

}


void Turning_led(uint8_t led_bits){
				ret_code_t err_code_5;
				uint8_t comm[2]={PCAL6804_OUTPUT_REG,led_bits };
				err_code_5 = nrf_drv_twi_tx(&m_twi,PCAL6804_ADDRESS ,comm, sizeof(comm), true);
				if (err_code_5 == NRF_SUCCESS) 
				{
					PrintServerPrintf("Turning on led(s) \n\r");
				}else{			
					PrintServerPrintf("Button(s) released \n\r");
								}
				
}

int pcal6408_init(void){   
			
				twi_init();
				Reg_config();
				return 0;
	
}


