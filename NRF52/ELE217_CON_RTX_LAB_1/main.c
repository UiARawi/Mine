/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "lamp_control.h"
#include "boards.h"
#include "print_server.h"
#include "switch_monitor.h"
#include "saadc.h"


extern int LampControlInit(void);
extern void PrintServerPrintf(const char *fmt, ...) ;
extern int saadc_main_init(void);

/*
 * main: initialize and start the system
 */

int main (void) {
	
  osKernelInitialize ();   // initialize CMSIS-RTOS
  
  // initialize peripherals here
	LampControlInit ();
	PrintServerInit();
	SwitchMonitorInit();
	saadc_main_init();
	
	

  osKernelStart ();   
}
