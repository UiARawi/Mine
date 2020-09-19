
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

#include "spi.h"
#include "TWI.h"

#define READY_TO_SPIS 0x88

volatile bool INT_ON_17 ;//interrupt pin flag
volatile bool INT_FROM_SLAVE;//interrupt pin flag
volatile bool spi_xfer_done = false;// done flag spi

uint8_t rx_buff_copy[10]={0xFF};//buffer to save the recieved data from slave
uint8_t button_read;
uint8_t dummy [2];
int main(void)
{
	
	
		master_configuratin();// configure the master
		nrf_delay_ms(10);
		twi_init ();// init the twi
		nrf_delay_ms(10);
		Reg_config();// configure registers in PCAL6408
		nrf_delay_ms(10);
		gpiote_init();//init the gpiote pins
		nrf_delay_ms(10);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();
		
    
		
		dummy [0]=READY_TO_SPIS;
		dummy [1]=0xFF;
		button_read = Read_input_reg();// read input register to reset the interrupt pin
		Turning_led(&dummy[1]);
		
		while (1)
    {			

						
				if(INT_ON_17){
				
				INT_ON_17 = false;
					
				button_read = Read_input_reg();// read input register
							
				uint8_t Se_t_Sl[2]={0x20, button_read};
				
				spi_xfer_done = false;
				
				spi_tx(Se_t_Sl);// start the transfer
				
				nrf_delay_us(500);
				
					if(spi_xfer_done){// the treansfer is done
					Turning_led(&rx_buff_copy[0]);
					}	
					
			
				}	else if(INT_FROM_SLAVE){//read input pin connected to input pin 8 on SPI master	
					INT_FROM_SLAVE = false;
					
					button_read = Read_input_reg();// read input register
					
					uint8_t Se_t_Sl[2]={0x20, button_read};

					spi_xfer_done = false;

					spi_tx(Se_t_Sl);// start the transfer

					nrf_delay_us(500);

							if(spi_xfer_done){// the treansfer is done
							Turning_led(&rx_buff_copy[0]);
							}	
							
					
				}
						
//				while ((!INT_ON_17) && (!INT_FROM_SLAVE))
//				{
//						__SEV();
//						__WFE();
				
//						__WFE();
//				}

    }
		
}
