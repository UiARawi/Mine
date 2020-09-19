
#include "cmsis_os.h"
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "switch_monitor.h"
#include "boards.h"
#include "print_server.h"
#include "lamp_control.h"
#include "saadc.h"

#ifdef BSP_BUTTON_0 
#define SWITCH_1 BSP_BUTTON_0 
#ifndef SWITCH_1 
 #error "Please indicate switch 1 input pin"
#endif
#endif 





bool __svc(1) init_GPIOTE (void);	

bool ADC_measuring = false;





void SwitchMonitor (void const *argu);

osMessageQDef(switch_msg_q, 16, message_t);																//define message queue
osMessageQId  switch_msg_qid;

osThreadId SwitchMonitor_ID;                                          // thread id

osThreadDef (SwitchMonitor, osPriorityAboveNormal, 1, 0);


void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

bool SwitchMonitorInit(void) {
	
	switch_msg_qid = osMessageCreate(osMessageQ(switch_msg_q), NULL);
  init_GPIOTE();
	
	SwitchMonitor_ID = osThreadCreate (osThread(SwitchMonitor),NULL);
	
	return true;
	
}

bool __SVC_1(void){
	
	nrfx_err_t nrfx_err; 
	
	nrfx_gpiote_in_config_t switch_config = NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI(true); 
	
	switch_config.pull = NRF_GPIO_PIN_PULLUP; 
	
	nrfx_err = nrfx_gpiote_init(); 
	
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(SWITCH_1, &switch_config, SwitchMonitorInterruptCB); 
	if (nrfx_err != NRF_SUCCESS) return false; 

	nrfx_gpiote_in_event_enable(SWITCH_1, true); 

	
  return true;

}
void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)

{
osMessagePut(switch_msg_qid, (uint32_t)pin, 0);
}

void SwitchMonitor (void const *argu)
{
	
	while (1) {
        osEvent evt = osMessageGet(switch_msg_qid, osWaitForever);						//wait for message to arrive
				switch(evt.value.v) {													                      //check pin value have received a message
					
					case SWITCH_1:
						if (ADC_measuring) { 
						 
						osSignalSet(saadc_id, SIGNAL_ADC_STOP_MEASURING);
						
						ADC_measuring = false;							
						} else {
						
						osSignalSet(saadc_id, SIGNAL_ADC_START_MEASURING);
						ADC_measuring = true;
					 
							}
						PrintServerPrintf("SWITCH 1 pressed\r\n");
					break;

					default:
					break;
						
				}
			}
		}
