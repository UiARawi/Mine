
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
osThreadId Led1_ID, Led2_ID, Led3_ID, Led4_ID;                                          // thread id

osSemaphoreId semMultiplex_ID;						//declare the Semaphore
osSemaphoreDef(semMultiplex);


osThreadDef (LampControl, osPriorityNormal, 4, 0);                   // thread object


int LampControlInit (void) {

  
	bsp_board_init(BSP_INIT_LEDS);
	
	semMultiplex_ID = osSemaphoreCreate(osSemaphore(semMultiplex), 4);
	
	Led1_ID = osThreadCreate (osThread(LampControl),(void *) led_1);
	Led2_ID = osThreadCreate (osThread(LampControl),(void *) led_2);
	Led3_ID = osThreadCreate (osThread(LampControl),(void *) led_3);
	Led4_ID = osThreadCreate (osThread(LampControl),(void *) led_4);
  if (!Led1_ID) return(-1);
	if (!Led2_ID) return(-1);
	if (!Led3_ID) return(-1);
	if (!Led4_ID) return(-1);
	

	
	
  return(0);
}

void LampControl (void const *argument) {
  uint32_t Waiting = 0;
  uint8_t Running = 0;
  while (1) {
		osEvent event = osSignalWait (0x00,Waiting);
		if(event.value.signals == 0x01){
      Waiting = 500;	
			Running = 1;
		}else if(event.value.signals == 0x02)
		{
			Waiting = 0xFFFFFFFF;
			Running = 0;
		}
		osSemaphoreWait(semMultiplex_ID,osWaitForever); 
		
		switch (Running){
			case 1:
		
		bsp_board_led_on((uint32_t)argument);  // turn on the led 
		PrintServerPrintf("LED %d turned ON\n\r ",(uint32_t) argument +1);
		osDelay(400*(uint32_t) argument+ 40);
		
		
		bsp_board_led_off((uint32_t)argument); //turn off the led
		PrintServerPrintf("LED %d turned OFF\n\r ",(uint32_t) argument +1);
		osDelay(400*(uint32_t) argument+ 400);
		
		
	
			break;
			
			case 0:
				bsp_board_led_off((uint32_t)argument + 1);
			  osDelay(500);
			break;
		}
			osSemaphoreRelease(semMultiplex_ID);  //release the Semaphore
		
	}


}

