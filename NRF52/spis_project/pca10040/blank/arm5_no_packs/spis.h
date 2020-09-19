#ifndef INCLUSION_GUARD_SPI_H
#define INCLUSION_GUARD_SPI_H


#include "nrf_drv_spis.h"

extern volatile bool spis_xfer_done;/**< Flag used to indicate that SPI instance completed the transfer. */
extern volatile bool spis_buffer_set;
extern uint8_t rx_buff_copy[10];

void spi_slave_configuratin(void);
void spis_tx(uint8_t *array);
 

#endif
