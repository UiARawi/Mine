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
#include "spis.h"
#include "TWIS.h"


extern uint8_t button_read;
volatile bool spis_buffer_set = false;
#define SPIS_INSTANCE  2 /**< SPI instance index. */
static const nrf_drv_spis_t spis = NRF_DRV_SPIS_INSTANCE(SPIS_INSTANCE);  /**< SPI instance. */

void spis_event_handler(nrf_drv_spis_event_t event);
#define Initia_value 0x0f
uint8_t       m_tx_buf[sizeof(Initia_value)];           /**< TX buffer. */
uint8_t       m_rx_buf[sizeof(Initia_value) + 1];    /**< RX buffer. */
static const uint8_t m_length = sizeof(m_tx_buf);        /**< Transfer length. */

/**
 * @brief SPI user event handler.
 * @param event
 */
void spis_event_handler(nrf_drv_spis_event_t event)
{		

    if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
    {		
			NRF_LOG_INFO(" Transfer completed.\n\r");
			NRF_LOG_INFO("Received: 0x%x",m_rx_buf[1]);
			spis_xfer_done = true;
			if(m_rx_buf[1]!= 0x00){
			rx_buff_copy[0] = m_rx_buf[1];
			 }
			nrf_gpio_pin_write(GPIO_PIN_8, S_ON);
		
    }else if(event.evt_type == NRF_DRV_SPIS_BUFFERS_SET_DONE){
			spis_buffer_set = true;
			
		
		}

}

void spi_slave_configuratin(void){

    nrf_drv_spis_config_t spis_config = NRF_DRV_SPIS_DEFAULT_CONFIG;
    spis_config.csn_pin   = APP_SPIS_CS_PIN;//pin 31
    spis_config.miso_pin = APP_SPIS_MISO_PIN;//pin 30
    spis_config.mosi_pin = APP_SPIS_MOSI_PIN;//pin 29
     spis_config.sck_pin  = APP_SPIS_SCK_PIN;//pin 28
    APP_ERROR_CHECK(nrf_drv_spis_init(&spis, &spis_config, spis_event_handler));

}


void spis_tx(uint8_t *array){
	
			// Reset rx buffer and transfer done flag
			memset(m_rx_buf, 0, m_length);

			APP_ERROR_CHECK(nrf_drv_spis_buffers_set(&spis, array, sizeof(array), m_rx_buf, sizeof(array)));

			NRF_LOG_FLUSH();

}



