
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "spis.h"
#include "TWIS.h"

#define NOT_READY_TO_SPIM 0x77
volatile bool INT_ON_17 ;//interrupt pin flag
volatile bool spis_xfer_done = false;// done flag spi

uint8_t rx_buff_copy[10]={0xFF};//buffer to save the recieved data from master
uint8_t button_read;
uint8_t dummy [2];
int main(void)
{		
		spi_slave_configuratin();// configure the slave 
		nrf_delay_ms(10);
		twi_init ();// init the twi	
		nrf_delay_ms(10);
		Reg_config();// configure registers in PCAL6408
		nrf_delay_ms(10);
		gpiote_init();//init the gpiote pins
		nrf_delay_ms(10);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
		
		
		dummy [0]=NOT_READY_TO_SPIM;
		dummy [1]=0xFF;
		button_read = Read_input_reg();// read input register to reset the interrupt pin
		Turning_led(&dummy[1]);
		
		while (1)
    {							
					if(INT_ON_17){	
					
					INT_ON_17 = false;
						
					nrf_gpio_pin_write(GPIO_PIN_8, S_OFF);// setting low output pin connected to input pin 4 on SPI master
					button_read = Read_input_reg();// read input register 
					
					
					}
					
					uint8_t Se_t_Sl[2]={0x20, button_read};
					
					spis_xfer_done = false;
					
					spis_tx(Se_t_Sl);// set the buffer or recieve the data from SPI master
					
					nrf_delay_us(500);
					
					if(spis_xfer_done){// the treansfer is done
					
						Turning_led(&rx_buff_copy[0]);
					}
									
//				while (!INT_ON_17)
//				{
//						__WFI();
//				}
	
    }
}

//				if(!nrf_gpio_pin_read(GPIO_PIN_7)){// read input pin connected to output pin 3 on SPI master
