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
#include "SPI.h"
#include "print_server.h"
#include "switch_monitor.h"
#include "Twi_fx.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX



#define SPI_INSTANCE  1 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */


static RX_Mas_struct       			m_rx_buf;           						/**< RX buffer. */	

static TX_Mas_Data_struct       				m_tx_buf;           									/**< TX  buffer. */	

static RX_Mas_struct       			DATA_BLE_buf;														/**< BLE buffer. */

static const uint8_t rx_m_length 		= sizeof(m_rx_buf);        /**< Transfer length. */

static const uint8_t tx_m_length 			= sizeof(m_tx_buf);        			/**< Transfer length. */

static uint16_t current_cmd;



void SpiInit(void)
{
	ret_code_t err_code;
	//makes instanse of config struct and setts it to default
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = SPI_SS_PIN;
    spi_config.miso_pin = SPI_MISO_PIN;
    spi_config.mosi_pin = SPI_MOSI_PIN;
    spi_config.sck_pin  = SPI_SCK_PIN;
	//init SPI with config struct
    err_code = nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL);
			if (err_code != NRF_SUCCESS){}	

			
}
/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrf_drv_spi_evt_t const* p_event, void* p_context)
{
			spi_xfer_done = true;

			NRF_LOG_INFO("Transfer completed.");
			//Data to send to phone" ble function"
			DATA_BLE_buf 		= m_rx_buf;


}
//been called from ble function according to ble command
void SpiMaster(uint8_t ble_cmd)
{
		//struct instance to hold fault code
		ret_code_t err_code;
	
    while (1)
    {		
				current_cmd =  ble_cmd;
				if(spi_xfer_done)
				{

					// Reset rx buffer and transfer done flag
					memset(&m_rx_buf, 0, rx_m_length);
					spi_xfer_done = false;
					err_code = nrf_drv_spi_transfer(&spi, (uint8_t *)&m_tx_buf, sizeof(TX_Mas_Data_struct), (uint8_t *)&m_rx_buf, sizeof(TX_Mas_Data_struct));
					if (err_code != NRF_SUCCESS){
					NRF_LOG_INFO(" spi transfer failed\r\n");
					return;
					}else{
					NRF_LOG_INFO("Not ready for new spi transfer\n");
					}												
				}
				nrf_delay_ms(100);

		}
}
