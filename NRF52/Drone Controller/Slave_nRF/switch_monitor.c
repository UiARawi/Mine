#include <stdbool.h>
#include <nrfx_gpiote.h>
#include "nrf_delay.h"
#include "nrf_drv_timer.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "boards.h"
#include "switch_monitor.h"
#include "cmsis_os.h" //inneholder bla que
#include "print_server.h"
#include "DEFINES.h"
#include "Twi_fx.h"
#include "SPI.h"

#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

//sett an que id
osMessageQId twi_msg_qid;
//creats an que objekt whit 25 bytes storage
osMessageQDef(twi_msg_queue, 25, uint8_t);
//sett an que id
osMessageQId spi_msg_qid;
//creats an que objekt whit 25 bytes storage
osMessageQDef(spi_msg_queue, 25, uint8_t);


// defines a thread ID
osThreadId SwitchControl_id;   
// defines a thread object
osThreadDef (SwitchMonitor, osPriorityNormal, 1, 0); 

//extern uint8_t   	m_tx_buf[2];


void ExtCBInit (void)
{
	//plass å legge feil koder
	nrfx_err_t nrfx_err;
	//lager en instanse av en struct og legger på sense HItoLOW true
	nrfx_gpiote_in_config_t switch_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
	//setter og enabler iRQ på gpiot
	nrfx_err = nrfx_gpiote_init();			
		if (nrfx_err != NRFX_SUCCESS)
           PrintServerPrintf("IRQ init failed\n");
	//initialiserer en irq handler med calback fx og setter inn struckten med data
	nrfx_err = nrfx_gpiote_in_init(PCAL6408_INT_PIN_NR, &switch_config, SwitchMonitorInterruptCB);	
		if (nrfx_err != NRFX_SUCCESS)
            PrintServerPrintf("IRQ handler init failed\n");
	nrfx_gpiote_in_event_enable(PCAL6408_INT_PIN_NR, true);			
		if (nrfx_err != NRFX_SUCCESS)
            PrintServerPrintf("IRQ handler enabledefailed\n");			
}

bool SwitchMonitorInit(void)
{
	/*make a ques*/
	twi_msg_qid = osMessageCreate(osMessageQ(twi_msg_queue),NULL);
	spi_msg_qid = osMessageCreate(osMessageQ(spi_msg_queue),NULL);
	/*make a thread*/
	SwitchControl_id = osThreadCreate (osThread(SwitchMonitor), NULL);
	return true;
}

//polarity is: In Task mode: Clear pin from OUT[n] task. Event mode: Generate IN[n] event when falling edge on pin
//so when sw is pressed signal sett in cb fx of interupt handler
void SwitchMonitorInterruptCB(uint32_t pin, nrf_gpiote_polarity_t polarity)
{	
	//set signal to switchmonitor
		osMessagePut(twi_msg_qid, (uint32_t)pin, 0);	
}

void SwitchMonitor(void const *argument)
{
	uint8_t sample_data;
	static uint8_t last_state = 0x00;
	
	while(1)
	{	
		//when sw pressed signal event from cb ISR
		osMessageGet(twi_msg_qid, osWaitForever);
		//read and save input reg
			sample_data = SLAVE_Read (PCAL6408_ADDRESS, PCAL6408_INPUT_REG);
			//check for nr of switch and toggel ledbit corresponding to sw
			for (int i=1; i< 5; i++)
				{
					if (CHECK_BIT(sample_data, i - 1))
						{
							//toggel led according to last state and sw nr pressed
							last_state ^= 1UL << (i+3);
							//send data to message queue to spi	
							//osMessagePut(spi_msg_qid,(uint8_t)last_state,0);
							//PrintServerPrintf("Switch nr:%x presed.\n",i);
							//m_tx_buf[0] = last_state;
						}
					//send data to message queue to spi	
					osMessagePut(spi_msg_qid,(uint8_t)last_state,0);
				}	
	}
}
