
#include "cmsis_os.h"
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "switch_monitor.h"
#include "boards.h"
#include "print_server.h"
#include "PCAL6408.h"

#define PCAL6408_INT 17

bool __svc(1) init_GPIOTE (void);	

extern uint8_t Read_input_reg(void);
extern void Turning_led(uint8_t led_bits);

void Pcal6408InterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void pcal6408 (void const *argument_pcal);
void SwitchMonitor (void const *argu);

osMessageQDef(switch_msg_q, 16, message_t);																//define message queue
osMessageQId  switch_msg_qid;

osThreadId SwitchMonitor_ID;                                          // thread id
osThreadDef (SwitchMonitor, osPriorityAboveNormal, 1, 0);

osThreadId pcal6408_id;
osThreadDef(pcal6408, osPriorityNormal, 1, 0 );

bool SwitchMonitorInit(void) {
	
	switch_msg_qid = osMessageCreate(osMessageQ(switch_msg_q), NULL);
  init_GPIOTE();
	SwitchMonitor_ID = osThreadCreate (osThread(SwitchMonitor),NULL);
	pcal6408_id = osThreadCreate (osThread(pcal6408),NULL);
	
	return true;	
}

bool __SVC_1(void){
	
	nrfx_err_t nrfx_err; 
	nrfx_gpiote_in_config_t switch_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
	switch_config.pull=NRF_GPIO_PIN_PULLUP;
	nrfx_err = nrfx_gpiote_init(); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_err = nrfx_gpiote_in_init(PCAL6408_INT, &switch_config, Pcal6408InterruptCB); 
	if (nrfx_err != NRF_SUCCESS) return false; 
	nrfx_gpiote_in_event_enable(PCAL6408_INT, true); 
  return true;

}

void SwitchMonitor (void const *argu)
{
	uint8_t Data_recieved;
	
	while (1) {
 
	osEvent event_int = osSignalWait(0x04,osWaitForever);
	
	Data_recieved=Read_input_reg();	//read from slave register
	Data_recieved = ~Data_recieved;//invert the bits 
	Data_recieved = Data_recieved << 4;// left shift the bits 
	uint8_t Data_send_to_led = ~Data_recieved;//invert the bits


	 osMessagePut(switch_msg_qid, (uint32_t)Data_send_to_led, NULL);

	
	}
}
void Pcal6408InterruptCB(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
       osSignalSet(SwitchMonitor_ID,0x04);	
}
void pcal6408 (void const *argument_pcal){

while(1){
		osEvent event_pcal = osMessageGet (switch_msg_qid,osWaitForever);
		Turning_led((uint8_t)event_pcal.value.v);
	}
}

