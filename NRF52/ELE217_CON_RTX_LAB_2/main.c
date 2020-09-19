/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "boards.h"
#include "print_server.h"
#include "switch_monitor.h"
#include "PCAL6408.h"

/*
 * main: initialize and start the system
 */

int main (void) {
	
  osKernelInitialize ();   // initialize CMSIS-RTOS
  
  // initialize peripherals here
	PrintServerInit();
	
	SwitchMonitorInit();
	
	pcal6408_init();

  osKernelStart ();   
}
