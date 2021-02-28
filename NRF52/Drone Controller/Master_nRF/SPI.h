#ifndef SPI_H
#define SPI_H

#include "nrf_drv_spi.h"
#include <stdint.h>



typedef struct
{
		int16_t x_data;
		int16_t y_data;
		int16_t x_angle;
		int16_t y_angle;
		uint16_t m1_thrust;
		uint16_t m2_thrust;
		uint16_t m3_thrust;
		uint16_t m4_thrust;
		uint16_t m1_current;
		uint16_t m2_current;
		uint16_t m3_current;
		uint16_t m4_current;

}RX_Mas_struct;




typedef struct
{
	int16_t x_angle_desired;
	int16_t y_angle_desired;
	uint16_t cmd;

}TX_Mas_Data_struct;

void SpiInit(void);
void spi_event_handler(nrf_drv_spi_evt_t const* p_event,void* p_context);
void SpiMaster(uint8_t ble_cmd);

#endif // SPI_H
