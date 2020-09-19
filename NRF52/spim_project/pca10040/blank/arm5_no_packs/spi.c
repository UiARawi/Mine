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

extern uint8_t button_read;
#define SPI_INSTANCE  2 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */

#define Initia_value 0x0f
uint8_t       m_tx_buf[sizeof(Initia_value)];           /**< TX buffer. */
uint8_t       m_rx_buf[sizeof(Initia_value) + 1];    /**< RX buffer. */
static const uint8_t m_length = sizeof(m_tx_buf);        /**< Transfer length. */

/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{		

    if (p_event->type == NRF_DRV_SPI_EVENT_DONE)
    {		
			NRF_LOG_INFO(" Transfer completed.\n\r");
			NRF_LOG_INFO("Received: 0x%x",m_rx_buf[1]);
			rx_buff_copy[0] = m_rx_buf[1];
			spi_xfer_done = true;

    }

}

void master_configuratin(void){
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
		spi_config.frequency = NRF_DRV_SPI_FREQ_125K;
    spi_config.ss_pin   = SPI_SS_PIN;//PIN 31
    spi_config.miso_pin = SPI_MISO_PIN;//PIN 30
    spi_config.mosi_pin = SPI_MOSI_PIN;//PIN 29
    spi_config.sck_pin  = SPI_SCK_PIN;//PIN 28
	
    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));

    NRF_LOG_INFO("SPI example started.");
		NRF_LOG_FLUSH();

}


void spi_tx(uint8_t *array){
	
		// Reset rx buffer and transfer done flag
		memset(m_rx_buf, 0, m_length);
		
		APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, array, sizeof(array), m_rx_buf, sizeof(array)));
//		nrf_delay_us(500);
		NRF_LOG_FLUSH();
		
		
}

