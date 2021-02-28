#include "nrf_drv_spis.h" 
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "SPI.h"
#include "print_server.h"
#include "switch_monitor.h"
#include "Twi_fx.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX


/**< SPIS instance index. */
#define SPIS_INSTANCE 1

bool TWI_SPI_TOKEN = false; 
//sett extern que id
//extern osMessageQId spi_msg_qid;

/**< SPIS instance. */
static const nrf_drv_spis_t spis = NRF_DRV_SPIS_INSTANCE(SPIS_INSTANCE);

/**< Flag used to indicate that SPIS instance completed the transfer. */
static volatile bool spis_xfer_done; 

//#define TEST_STRING "Nordic"
static TX_Slave_struct       				m_tx_buf;       /**< TX buffer. */


static RX_SLAVE_Data_struct       m_rx_buf;    /**< RX buffer. */

static uint16_t current_cmd;

// Thread ID 
osThreadId spis_thread_id; 

// Thread Object 
osThreadDef (SpiSlave, osPriorityNormal, 1, 0); 

osMailQDef(spis_mail_Q, 16, RX_SLAVE_Data_struct);
osMailQId spis_mail_ID;

osMailQDef(twi_write_mail_Q, 8, RX_SLAVE_Data_struct);
osMailQId twi_write_mail_ID;


void SpiInit (void)
{
	//bsp_board_init(BSP_INIT_LEDS);  
	ret_code_t err_code; 
	
	// Init NRF LOG 
	err_code = NRF_LOG_INIT(NULL); 	
	if(err_code != NRF_SUCCESS) {PrintServerPrintf("NRF_LOG_INIT failed in Spi_Init");} 
	
	NRF_LOG_DEFAULT_BACKENDS_INIT(); 
		
	// Make instance of config struct, set to default 
		nrf_drv_spis_config_t spis_config = NRF_DRV_SPIS_DEFAULT_CONFIG;
    spis_config.csn_pin               = APP_SPIS_CS_PIN;
    spis_config.miso_pin              = APP_SPIS_MISO_PIN;
    spis_config.mosi_pin              = APP_SPIS_MOSI_PIN;
    spis_config.sck_pin               = APP_SPIS_SCK_PIN;
		
		// Init SPI with config struct 
		err_code = nrf_drv_spis_init(&spis, &spis_config, SpisEventHandler); 
		if(err_code != NRF_SUCCESS){PrintServerPrintf("NRF_DRV_SPIS_INIT FAILED in Spi_init\n");} 
		PrintServerPrintf("SPI Slave started\n"); 
		memset(&m_rx_buf, 0, sizeof(RX_SLAVE_Data_struct));	
		spis_xfer_done = false;
	
		if (nrf_drv_spis_buffers_set(&spis, (uint8_t*)&m_tx_buf, sizeof(TX_Slave_struct), (uint8_t*)&m_rx_buf, sizeof(RX_SLAVE_Data_struct)) != NRF_SUCCESS)
			{
				PrintServerPrintf("Failed to set SPIS buffers!");
			}
		
		NRF_POWER->TASKS_CONSTLAT = 1;
	
		spis_mail_ID 					= osMailCreate(osMailQ(spis_mail_Q), NULL);
		twi_write_mail_ID 		= osMailCreate(osMailQ(twi_write_mail_Q), NULL);

			
		// Create a thread
		spis_thread_id = osThreadCreate (osThread(SpiSlave), NULL); 
}


void SpisEventHandler(nrf_drv_spis_event_t event)
{
      if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
				{
          spis_xfer_done = true;
					PrintServerPrintf(" Transfer completed. Rx data (cmd: 0x%02x) mailed to SpiSlave thread.\r\n", m_rx_buf.cmd);
			   	
					if (m_rx_buf.cmd == DESIRED_DEG_CMD)
						{
							RX_SLAVE_Data_struct *rx_spi = (RX_SLAVE_Data_struct *)osMailAlloc(twi_write_mail_ID, 0);
							memcpy(rx_spi, &m_rx_buf, sizeof(RX_SLAVE_Data_struct));
							current_cmd= m_rx_buf.cmd;
							osMailPut(twi_write_mail_ID, rx_spi);
						}
					else
						{
							PrintServerPrintf(" Transfer completed. Failed to mail RX data (cmd:0x%02x) to SpiSlave thread.\r\n", m_rx_buf.cmd);
						}
						

				}		
}




void SpiSlave (void const *arg)
{

	// Hold fault code 
	ret_code_t err_code; 
	// Hold event 
	osEvent evt;
	
	while(1)
	{		
			
			TX_Slave_struct *mail_spi = NULL;
			//wait for mail from threads
			evt = osMailGet(spis_mail_ID, osWaitForever); 
			if (evt.status != osEventMail)
			{
			PrintServerPrintf("No mail /r/n");
			continue;
			}
			mail_spi = (TX_Slave_struct *)evt.value.p;

			m_tx_buf = *mail_spi;
			if (spis_xfer_done){

			memset(&m_rx_buf, 0 , sizeof(RX_SLAVE_Data_struct)); 
			spis_xfer_done = false; 

			err_code = nrf_drv_spis_buffers_set(&spis, (uint8_t*)&m_tx_buf, sizeof(TX_Slave_struct), (uint8_t*)&m_rx_buf, sizeof(RX_SLAVE_Data_struct));
			if(err_code != NRF_SUCCESS) {PrintServerPrintf(" XXXXXX \r\n");}

			}

			osMailFree(spis_mail_ID, mail_spi);
			mail_spi = NULL;

			PrintServerPrintf("SpiSlave main thread is  OK!\r\n");
	}
	}

