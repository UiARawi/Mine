#include "cmsis_os.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"

#include "print_server.h"



#define ADC_RES_10BIT                     1024  
#define ADC_RES_12BIT                     4096  
#define SAADC_CH_CONFIG_REFSEL_mV           600
#define ADC_PRE_SCALING_COMPENSATION        6
#define SAMPLES_IN_BUFFER 5
volatile uint8_t state = 1;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(0);//koniguere timer instancen
static nrf_ppi_channel_t     m_ppi_channel; //Kanal i PPI (Event END POINT(HER Timer) and TASK END POINT (Her ADC))
static uint32_t              m_adc_evt_counter;

bool __svc(2) saadc_init_SVC(void);
void saadc(void const *msg);
bool start_printing = true;

typedef struct {
    nrf_saadc_value_t ADCData[SAMPLES_IN_BUFFER];
} message_t;
 
osPoolDef(mpool, 5, message_t);																		//define memory pool
osPoolId  mpool_ID;

osMessageQDef(saadc_queue, 16, message_t);																//define message queue
osMessageQId  saadc_queue_ID;

osThreadId saadc_id;
osThreadDef (saadc, osPriorityNormal, 1, 0);

void timer_handler(nrf_timer_event_t event_type, void * p_context)
{

}

int saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{   
	
	
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
				message_t *message;																							//define pointer for memory pool buffer
				message = (message_t*)osPoolAlloc(mpool_ID);										//Allocate a memory pool buffer
				if(!message)return (-1);
			
        ret_code_t err_code;
			  

			osMessagePut(saadc_queue_ID,(uint32_t) p_event->data.done.p_buffer, 0);
			
			err_code = nrf_drv_saadc_buffer_convert(message->ADCData, SAMPLES_IN_BUFFER);
      if (err_code!= NRF_SUCCESS)return false;
				
    } 
		return 1;
}

void saadc(void const *msg)
{ uint32_t Waiting_state = 0;
  uint8_t Measuring = 0;
	while(1){
					osEvent event = osSignalWait (0x00,Waiting_state);
					if(event.value.signals == 0x03){
					Waiting_state = 500;	
					Measuring = 1;
					}else if(event.value.signals == 0x04)
					{
					Waiting_state = 0xFFFFFFFF;
					Measuring = 0;
					}
					else{									//jumps to while(1)-starten av lukket
					continue;
					}
						
		     
				switch(Measuring){
					case 1:
					 nrf_drv_timer_resume(&m_timer);
					 start_printing = true;
					break;
					
					case 0:
						nrf_drv_timer_pause(&m_timer);
						start_printing = false;
						break;
			}
				if(start_printing){
					osEvent evt = osMessageGet(saadc_queue_ID, Waiting_state);						//wait for message to arrive
					if (evt.status == osEventMessage) {													//check we have received a message
					message_t *message = (message_t*)evt.value.p;						//read the pointer to memory pool buffer
					PrintServerPrintf("ADC event number: %d \n\r", (int)m_adc_evt_counter);
					for(int i=0; i < SAMPLES_IN_BUFFER; i++)
					{

					PrintServerPrintf("VDD %d mV\n\r ",((message->ADCData[i]*(SAADC_CH_CONFIG_REFSEL_mV)*(ADC_PRE_SCALING_COMPENSATION))/(ADC_RES_12BIT)));			
					}		
					m_adc_evt_counter++;					
					osPoolFree(mpool_ID, message);															//Release the buffer
        }else{
				PrintServerPrintf("NO ADC esample is taken\n\r");
				}
			}
		}
					

}


int  saadc_init(void)
{

		saadc_init_SVC();
		return 1;

}

bool __SVC_2 (void)
{
	  message_t *m_buffer_pool_1;
	  message_t *m_buffer_pool_2;
	  m_buffer_pool_1 = (message_t*)osPoolAlloc(mpool_ID);
	  m_buffer_pool_2 = (message_t*)osPoolAlloc(mpool_ID);
      ret_code_t err_code;
	/*Analog-to-digital converter channel configuration structure.*/
	
	/*
  Macro for setting nrf_saadc_channel_config_t to default settings
         in single ended mode. PIN_P Analog input.*/
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);
		
		nrfx_saadc_config_t drv_config = NRFX_SAADC_DEFAULT_CONFIG;
     //Function for initializing the SAADC.
    err_code = nrfx_saadc_init(&drv_config,(nrfx_saadc_event_handler_t) saadc_callback);
    if (err_code!= NRF_SUCCESS)return false;
     //Function for initializing an SAADC channel.This function configures and enables the channel.
    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    if (err_code!= NRF_SUCCESS)return false;

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool_1->ADCData, SAMPLES_IN_BUFFER);
    if (err_code!= NRF_SUCCESS)return false;

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool_2->ADCData, SAMPLES_IN_BUFFER);
    if (err_code!= NRF_SUCCESS)return false;
		

    err_code = nrf_drv_ppi_init(); //Function for initializing PPI module
																	//NRF_SUCCESS	If the module was successfully initialized.
																	//NRF_ERROR_MODULE_ALREADY_INITIALIZED	If the module has already been initialized.
	
    if (err_code!= NRF_SUCCESS)return false;

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;//TIMER instance configuration.
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32; //Den structen har flere parametere
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);//Function for initializing the timer.
    if (err_code!= NRF_SUCCESS)return false;

    /* setup m_timer for compare event every 400ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
	//Function for setting the timer channel in extended compare mode.
    nrf_drv_timer_extended_compare(&m_timer,                          
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
																	 
                                   false);
    nrf_drv_timer_enable(&m_timer);
     //Function for returning the address of a specific timer compare event.
    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
			//Function for getting the address of a SAMPLE SAADC task. 	

    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
		//Function for allocating a PPI channel.This function allocates the first unused PPI channel.
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    if (err_code!= NRF_SUCCESS)return false;
    //Function for assigning task and event endpoints to the PPI channel.
    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    if (err_code!= NRF_SUCCESS)return false;
		
		//Function for enabling a PPI channel.
    err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    if (err_code!= NRF_SUCCESS)return false;
	
		
		return true;
}

/**
 * @brief Function for main application entry.
 */
int saadc_main_init(void )
{   saadc_queue_ID = osMessageCreate(osMessageQ(saadc_queue),NULL);
		if(!saadc_queue_ID)return (-1);
    mpool_ID = osPoolCreate(osPool(mpool));
		if(!mpool_ID)return (-1);
    saadc_id = osThreadCreate(osThread(saadc), NULL);
		if(!saadc_id)return (-1);
    
	  saadc_init();
	  

   return 1;
		
		
}




/** @} */
