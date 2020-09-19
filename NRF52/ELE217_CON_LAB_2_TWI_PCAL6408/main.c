

#include "nrf_delay.h"
#include "pcal6480.h"

#define PCAL6408_INT 17
#define FF_hex 0xFF
#define PCAL6804_ADDRESS 0X20
extern volatile bool INT_ON_17 ;
extern uint8_t Data_recieved;
extern uint8_t Data_send_to_output;
extern uint8_t recieved_data;

int main(void){   					
				APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
				NRF_LOG_DEFAULT_BACKENDS_INIT();
				
				twi_init();
				
	
				NRF_LOG_INFO("TWI scanner started.");
				NRF_LOG_FLUSH();

				Reg_config();
				gpiote_init();

        while(1){
				if (INT_ON_17) {
					
					INT_ON_17=false;
					
					uint8_t Data_recieved=Read_input_reg();	//read from slave register
					NRF_LOG_INFO(" Raw Data_recieved : 0x%x", Data_recieved);
					NRF_LOG_FLUSH();
					Data_recieved = ~Data_recieved;//invert the bits 
					NRF_LOG_INFO("Data_recieved inverted : 0x%x", Data_recieved);
					NRF_LOG_FLUSH();
					Data_recieved = Data_recieved & 0x0F;
					NRF_LOG_INFO("Data_recieved & 0x0F(sent to Button) : 0x%x", Data_recieved);
					NRF_LOG_FLUSH();
					nrfx_gpiote_in_event_disable(PCAL6408_INT);
					BUTTON_NUMBER(Data_recieved);//print out the pushed buttons
					nrfx_gpiote_in_event_enable(PCAL6408_INT, true);
					Data_recieved = Data_recieved << 4;// left shift the bits 
					NRF_LOG_INFO("Data_recieved shifted to lift : 0x%x", Data_recieved);
					NRF_LOG_FLUSH();
					Data_recieved = ~Data_recieved;//invert the bits
					NRF_LOG_INFO("Inverted Data_recieved shifted to lift : 0x%x", Data_recieved);
					NRF_LOG_FLUSH();
					uint8_t Data_send_to_output = Data_recieved ;//data to send to output register(Leds)
					NRF_LOG_INFO("Inverted Data_recieved shifted to lift(SENT TO LEDS): 0x%x", Data_send_to_output);
					NRF_LOG_FLUSH();
					
					
					Turning_led(Data_send_to_output);
					
				
				
			}
	}
}

/** @} */
