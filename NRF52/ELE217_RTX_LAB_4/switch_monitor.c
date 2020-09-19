
#include "cmsis_os.h"
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "switch_monitor.h"
#include "boards.h"
#include "print_server.h"
#include "lamp_control.h"

#ifdef BSP_BUTTON_0 
#define SWITCH_1 BSP_BUTTON_0 
#ifndef SWITCH_1 
 #error "Please indicate switch 1 input pin"
#endif
#endif 

#ifdef BSP_BUTTON_1 
#define SWITCH_2 BSP_BUTTON_1 
#ifndef SWITCH_2 
#error "Please indicate switch 2 input pin"
#endif
#endif 

#ifdef BSP_BUTTON_2 
#define SWITCH_3 BSP_BUTTON_2 
#ifndef SWITCH_3 
#error "Please indicate switch 3 input pin"
#endif
#endif 

#ifdef BSP_BUTTON_3 
#define SWITCH_4 BSP_BUTTON_3 
#ifndef SWITCH_4 
#error "Please indicate switch 4 input pin"
#endif
#endif 



bool __svc(1) init_SwitchMonitor (void);	
bool lamp1_blinking = false; 
bool lamp2_blinking = false;
bool lamp3_blinking = false; 
bool lamp4_blinking = false;





void SwitchMonitor ();

osMessageQDef(switch_msg_q, 16, message_t);																//define message queue
osMessageQId  switch_msg_qid;

osThreadId SwitchMonitor_ID;                                          // thread id

osThreadDef (SwitchMonitor, osPriorityAboveNormal, 1, 0);


void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);

bool SwitchMonitorInit(void) {
	
	switch_msg_qid = osMessageCreate(osMessageQ(switch_msg_q), NULL);
  init_SwitchMonitor();
	
	SwitchMonitor_ID = osThreadCreate (osThread(SwitchMonitor),NULL);
	
	return true;
	
}

bool __SVC_1(void){
	
	nrfx_err_t nrfx_err; 
	nrfx_gpiote_in_config_t switch_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true); 
	switch_config.pull = NRF_GPIO_PIN_PULLUP; 
	nrfx_err = nrfx_gpiote_init(); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(SWITCH_1, &switch_config, SwitchMonitorInterruptCB); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(SWITCH_2, &switch_config, SwitchMonitorInterruptCB); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(SWITCH_3, &switch_config, SwitchMonitorInterruptCB); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(SWITCH_4, &switch_config, SwitchMonitorInterruptCB);
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_gpiote_in_event_enable(SWITCH_1, true); 
	nrfx_gpiote_in_event_enable(SWITCH_2, true); 
	nrfx_gpiote_in_event_enable(SWITCH_3, true); 
	nrfx_gpiote_in_event_enable(SWITCH_4, true); 
	
  return true;

}
void SwitchMonitorInterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)

{
osMessagePut(switch_msg_qid, (uint32_t)pin, 0);
}

void SwitchMonitor ()
{
	
	while (1) {
        osEvent evt = osMessageGet(switch_msg_qid, osWaitForever);						//wait for message to arrive
				switch(evt.value.v) {													                      //check pin value have received a message
					
					case SWITCH_1:
						if (lamp1_blinking) { 
						osSignalSet(Led1_ID, SIGNAL_LAMP_STOP_BLINKING); 
						lamp1_blinking = false; 
						} else {
						osSignalSet(Led1_ID, SIGNAL_LAMP_START_BLINKING); 
						lamp1_blinking = true; }
						PrintServerPrintf("SWITCH 1 pressed\r\n");
					break;
					
					case SWITCH_2:
						if (lamp2_blinking) { 
						osSignalSet(Led2_ID, SIGNAL_LAMP_STOP_BLINKING); 
						lamp2_blinking = false; 
						} else {
						osSignalSet(Led2_ID, SIGNAL_LAMP_START_BLINKING); 
						lamp2_blinking = true; }
						PrintServerPrintf("SWITCH 2 pressed\r\n");
					break;
						
					case SWITCH_3:
						if (lamp3_blinking) { 
						osSignalSet(Led3_ID, SIGNAL_LAMP_STOP_BLINKING); 
						lamp3_blinking = false; 
						} else {
						osSignalSet(Led3_ID, SIGNAL_LAMP_START_BLINKING); 
						lamp3_blinking = true; }
						PrintServerPrintf("SWITCH 3 pressed\r\n");
					break;
					
					case SWITCH_4:
						if (lamp4_blinking) { 
						osSignalSet(Led4_ID, SIGNAL_LAMP_STOP_BLINKING); 
						lamp4_blinking = false; 
						} else {
						osSignalSet(Led4_ID, SIGNAL_LAMP_START_BLINKING); 
						lamp4_blinking = true; }
						PrintServerPrintf("SWITCH 4 pressed\r\n");
					break;
					default:
					break;
						
				}
			}
		}
