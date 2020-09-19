/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "lamp_control.h"
#include "boards.h"
#include "print_server.h"


extern int LampControlInit(void);
extern void PrintServerPrintf(const char *fmt, ...) ;


/*
 * main: initialize and start the system
 */

int main (void) {
	const char Letter[] = "Heisann hoppsann";
  osKernelInitialize ();                    // initialize CMSIS-RTOS
  
  // initialize peripherals here
	LampControlInit ();
	
	

  osKernelStart ();                         // start thread execution 
}
