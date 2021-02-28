#include "cmsis_os.h"
#include "lamp_control.h"
#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "print_server.h"
#include "switch_monitor.h"
#include "nrf_drv_timer.h"
#include "saadc.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/


#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif



                        

// CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Thread 1 'LampControl': Sample thread
 *---------------------------------------------------------------------------*/
#define LED1 0 
#define LED2 1
#define LED3 2
#define LED4 3

/*threads*/
// Declared Lamp Control thread ids as external,
// i.e. they are defined in lamp_control.c
osThreadId lamp1_thread_id,lamp2_thread_id, lamp3_thread_id, lamp4_thread_id; 
osThreadDef (LampControl, osPriorityNormal, 4, 0); 														// thread object

int LampControlInit (void) 
	{
	 /* Configure board. */
  bsp_board_init(BSP_INIT_LEDS);
	/*Creat trhreds*/
	
  lamp1_thread_id = osThreadCreate (osThread(LampControl),(void *)LED1);
	lamp2_thread_id = osThreadCreate (osThread(LampControl),(void *)LED2);
	lamp3_thread_id = osThreadCreate (osThread(LampControl),(void *)LED3);
	lamp4_thread_id = osThreadCreate (osThread(LampControl),(void *)LED4);

  return(0);
}

void LampControl (void const *argument) 
{
	osEvent evt;
	
  while (1) 
		{	
			nrf_drv_timer_pause(&m_timer);
			evt = osSignalWait (SIGNAL_LED_ON,osWaitForever);
			PrintServerPrintf ("Led %i ON\n", (uint32_t)argument+1);
			nrf_drv_timer_resume(&m_timer);
				while (evt.value.signals != SIGNAL_LED_OFF)
					{
						bsp_board_led_invert((uint32_t)argument);
						evt = osSignalWait (0x00,500+((uint32_t)argument*100));			
					}  
		bsp_board_led_off ((uint32_t)argument);	
		PrintServerPrintf ("Led %i OFF\n", (uint32_t)argument+1);
		}
}

