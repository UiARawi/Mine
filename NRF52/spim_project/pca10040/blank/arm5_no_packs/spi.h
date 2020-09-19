#ifndef INCLUSION_GUARD_SPI_H
#define INCLUSION_GUARD_SPI_H


#include "nrf_drv_spi.h"

extern volatile bool spi_xfer_done;/**< Flag used to indicate that SPI instance completed the transfer. */

extern uint8_t rx_buff_copy[10];

void master_configuratin(void);
void spi_tx(uint8_t *array);
 

#endif
