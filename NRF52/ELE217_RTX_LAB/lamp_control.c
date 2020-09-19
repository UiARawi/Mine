
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "boards.h"

#define led_1 (0)
#define led_2 (1)
#define led_3 (2)
#define led_4 (3)
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 

void LampControl (void const *argument);                             // thread function
void callback(void const *param);


osThreadId Led1_ID, Led2_ID;                                          // thread id


osThreadDef (LampControl, osPriorityNormal, 2, 0);                   // thread object

osTimerDef(timer0,callback);
osTimerDef(timer1,callback);

int LampControlInit (void) {

	osStatus status_0;
	osStatus status_1;
  
	bsp_board_init(BSP_INIT_LEDS);
	
	osTimerId timer0_ID = osTimerCreate(osTimer(timer0), osTimerPeriodic, (void *) led_3);
	osTimerId timer1_ID = osTimerCreate(osTimer(timer1), osTimerPeriodic, (void *) led_4);
	if (!timer0_ID) return(-1);
	if (!timer1_ID) return(-1);


	status_0 = osTimerStart(timer0_ID, 0x5000);
	status_1 = osTimerStart(timer1_ID, 0x2000);
	if (status_0 != osOK) return (-1);
	if (status_1 != osOK) return (-1);
	
		
	Led1_ID = osThreadCreate (osThread(LampControl),(void *) led_1);
	Led2_ID = osThreadCreate (osThread(LampControl),(void *) led_2);
  if (!Led1_ID) return(-1);
	if (!Led2_ID) return(-1);
	

  return(0);
}

void LampControl (void const *argument) {

  while (1) {
		bsp_board_led_invert((uint32_t)argument);  // Insert thread code here...
		osDelay(800+(uint32_t)argument*600);
                                               
  }
}

 void callback(void const *param)
{

		bsp_board_led_invert((uint32_t)param);  

}



