#include <cmsis_os.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "print_server.h"


#include "saadc.h" 

#define SAMPLES_IN_BUFFER 5

volatile uint8_t state = 1;
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;

//define SaAdc thread 
void SaAdc (void const *argument); 

// Define thread
osThreadDef (SaAdc, osPriorityNormal, 1, 0); 
// Create thread ID 
osThreadId tid_SaAdc_1; 

// Create Msg Queue ID
osMessageQId Saadc_CB_msg_qid; 

// Define Message queue 
osMessageQDef(Saadc_msg_Queue, 5, (uint32_t)navn_t); 

// ADC message block
typedef struct
{
	nrf_saadc_value_t ADCdata[SAMPLES_IN_BUFFER];  
}Adc_Msg_Block_t; 

// Create adc pool id 
osPoolId Adc_Pool_Id;
// Define adc pool 
osPoolDef(Adc_Pool, 16, Adc_Msg_Block_t);


// Timer Handler not used 
void timer_handler(nrf_timer_event_t event_type, void * p_context) {} // DO NOTHING! 

void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

		// Checks if programmable peripheral interconnect (PPI) is initialized
    err_code = nrf_drv_ppi_init();
    if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_ppi_init has FAILED") ;}

		// Timer driver instance config. struct. (default config) 
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
	
		// Timer bitwidth config set to 32bit 
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
		
		// Initialize timer (p_instance, p_config, timer_event_handler)
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_timer_init has FAILED") ;}

    // Convert time in millisec to timer ticks (p_instance (driver instance struct), time_ms)
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
		
		// Set time channel in extended compare mode 
		nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0, //uses timer 0
                                   ticks,									//use tick timer
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, //resett counter on comper match
                                   false);								// disabel timer_handler
																	 
		// Turn on timer (p_instance (pont to driver instance struct)  
    nrf_drv_timer_enable(&m_timer);
		
		// sett adress of compare clear of NRF_TIMER_CHANNEL_0
    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    // Get addr. of a SAMPLE SAADC task 
		uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_ppi_channel_alloc has FAILED") ;}

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_ppi_channel_assign has FAILED") ;}
}
	
void saadc_sampling_event_enable(void)
{
		// Enable PPI channel, check for errors 
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);
    if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_buffer_convert has FAILED") ;}
}

void SaadcInit (void)
{ 
	// Create adc_pool
	Adc_Pool_Id = osPoolCreate(osPool(Adc_Pool));
	
	// Create adc message buffer 1 and 2 
	Adc_Msg_Block_t *adc_msg_buffer_1; 
	Adc_Msg_Block_t *adc_msg_buffer_2; 
	adc_msg_buffer_1 = (Adc_Msg_Block_t*) osPoolAlloc(Adc_Pool_Id);
  adc_msg_buffer_2 = (Adc_Msg_Block_t*) osPoolAlloc(Adc_Pool_Id);
	
	// Return Error Code instance 
	ret_code_t err_code;
	
	// Create message queue ID 
	Saadc_CB_msg_qid = osMessageCreate(osMessageQ(Saadc_msg_Queue), NULL); 
	
	// Create thread 
	tid_SaAdc_1 = osThreadCreate (osThread(SaAdc), NULL); 
	if(!tid_SaAdc_1) {PrintServerPrintf("tid_SaAdc_1 = osThreadCreate has FAILED") ;}
	
	// Configure/Enable input channel to AIN1-SE (analog input 1) SINGLE ENDED
	nrf_saadc_channel_config_t channel_config =
	NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);
	
	// Configure saads to default config(NULL), use saadc_CB as evt.handler
	err_code = nrf_drv_saadc_init(NULL, Saadc_Callback); //CB NOT CONF. YET
		if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_init has FAILED") ;} 
	
	// Init/enable of channel 0, use AIN1 as input (channel_config)
	err_code = nrf_drv_saadc_channel_init(0, &channel_config);
		if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_channel_init has FAILED") ;} 
	
	// Configure 2 SAADC buffers , Sets SAADC up for conversion 		
	err_code = nrf_drv_saadc_buffer_convert(adc_msg_buffer_1->ADCdata, SAMPLES_IN_BUFFER);
	if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_buffer_convert(1) has FAILED") ;}
	err_code = nrf_drv_saadc_buffer_convert(adc_msg_buffer_2->ADCdata, SAMPLES_IN_BUFFER);
	if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_buffer_convert(2) has FAILED") ;}
	
	// init/enable sampling event
	saadc_sampling_event_init(); 
	saadc_sampling_event_enable();
}

void Saadc_Callback(nrf_drv_saadc_evt_t const * p_event)
{	
		//navn_t navn_test;
	
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {		
				// define return code 
        ret_code_t err_code;
				if(err_code != NRF_SUCCESS ){PrintServerPrintf("adc_msg_buffer_3 alloc has FAILED");} 
					
				// send pointer of buffer back to ADC 
				err_code = nrf_drv_saadc_buffer_convert(((Adc_Msg_Block_t*) osPoolAlloc(Adc_Pool_Id))->ADCdata, SAMPLES_IN_BUFFER);
				if(err_code != NRF_SUCCESS ){PrintServerPrintf("nrf_drv_saadc_buffer_convert has FAILED") ;}
							
				// PUT msg into queue , recieve by saadc thread function 	
				osMessagePut(Saadc_CB_msg_qid, (uint32_t)p_event->data.done.p_buffer, 0);						
    }
}
void SaAdc (void const *argument)
{
	PrintServerPrintf("HAL SAADC started! \n");
	// Make a instans of event
	osEvent my_event;
	Adc_Msg_Block_t *message;
	while(1)
	{
		// sett values in to event 
		my_event = osMessageGet(Saadc_CB_msg_qid, osWaitForever);
		//make adc_msg... pointer and sett it to pointer from message 
		message = (Adc_Msg_Block_t*)my_event.value.p; 
		//print event number of adc
		PrintServerPrintf("ADC event number: %d\r\n", (int)m_adc_evt_counter);
		// increases counter of event number
    m_adc_evt_counter++;
		
		for(int i = 0; i < SAMPLES_IN_BUFFER; i++)
		{	
			// ADC data corrigated to mV and print to uart 
			PrintServerPrintf("%d mV.\r\n", message->ADCdata[i]*(3600)/(4094)); 
		}
		// Free pool
		osPoolFree(Adc_Pool_Id, message); 
	}
}

