
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "boards.h"
#include "print_server.h"

#define led_1 (0)
#define led_2 (1)
#define led_3 (2)
#define led_4 (3)
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 

void LampControl (void const *argument);                             // thread function
void callback(void const *param);

osMutexId uart_mutex_ID;
osMutexDef(uart_mutex);
osThreadId Led1_ID, Led2_ID, Led3_ID, Led4_ID;                                          // thread id

osSemaphoreId semMultiplex_ID;						//declare the Semaphore
osSemaphoreDef(semMultiplex);


osThreadDef (LampControl, osPriorityNormal, 4, 0);                   // thread object


int LampControlInit (void) {

  
	bsp_board_init(BSP_INIT_LEDS);
	
//	semMultiplex_ID = osSemaphoreCreate(osSemaphore(semMultiplex), 2);
	uart_mutex_ID = osMutexCreate(osMutex(uart_mutex));
	
	Led1_ID = osThreadCreate (osThread(LampControl),(void *) led_1);
	Led2_ID = osThreadCreate (osThread(LampControl),(void *) led_2);
	Led3_ID = osThreadCreate (osThread(LampControl),(void *) led_3);
	Led4_ID = osThreadCreate (osThread(LampControl),(void *) led_4);
  if (!Led1_ID) return(-1);
	if (!Led2_ID) return(-1);
	if (!Led3_ID) return(-1);
	if (!Led4_ID) return(-1);
	
	PrintServerInit();
	
	
  return(0);
}

void LampControl (void const *argument) {
  
  while (1) {
		osSemaphoreWait(semMultiplex_ID,osWaitForever);

		
		bsp_board_led_on((uint32_t)argument);  // Insert thread code here...
		osMutexWait(uart_mutex_ID, osWaitForever);
		PrintServerPrintf("LED %d turned ON\n\r ",(uint32_t) argument);
		osMutexRelease(uart_mutex_ID);
		osDelay(200*(uint32_t) argument+ 2000);
		
		bsp_board_led_off((uint32_t)argument);
		osSemaphoreRelease(semMultiplex_ID);
		osMutexWait(uart_mutex_ID, osWaitForever);
		PrintServerPrintf("LED %d turned OFF\n\r ",(uint32_t) argument);
		osMutexRelease(uart_mutex_ID);
		osDelay(300*(uint32_t) argument+ 3000);
		
		
		
                                               
  }
}




