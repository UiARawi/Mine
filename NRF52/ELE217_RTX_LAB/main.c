/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "lamp_control.h"
#include "boards.h"


extern int LampControlInit(void);


/*
 * main: initialize and start the system
 */
// 
	
//osThreadDef(LampControl, osPriorityAboveNormal, 2, 0);
int main (void) {
	
  osKernelInitialize ();                    // initialize CMSIS-RTOS
  
  // initialize peripherals here
	LampControlInit();
	
	
	// create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);

  osKernelStart ();                         // start thread execution 
}
