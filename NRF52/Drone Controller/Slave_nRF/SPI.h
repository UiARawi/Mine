#ifndef SPI_H 
#define SPI_H

#include "nrf_drv_spis.h" 
#include "cmsis_os.h"

/*Dataer til overføring*/
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

}TX_Slave_struct;



typedef struct
{
	int16_t x_angle_desired;
	int16_t y_angle_desired;
	uint16_t cmd;

}RX_SLAVE_Data_struct;

extern  osMailQId spis_mail_ID; 
extern osMailQId twi_write_mail_ID;;
void SpiInit(void); 

void SpisEventHandler(nrf_drv_spis_event_t event); 

void SpiSlave(void const *arg); 

#endif //SPI_H
