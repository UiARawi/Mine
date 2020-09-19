/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "lamp_control.h"
#include "boards.h"
#include "print_server.h"
#include "switch_monitor.h"

#define USE_PSP_IN_THREAD_MODE 2 //(1<<1)
#define THREAD_MODE_IS_UNPRIVILIGED 1
#define THREAD_MODE_IS_PRIVILIGED 0
#define PSP_STACK_SIZE 0x200

extern int LampControlInit(void);
extern void PrintServerPrintf(const char *fmt, ...) ;


/*
 * main: initialize and start the system
 */

int main (void) {

  osKernelInitialize ();   // initialize CMSIS-RTOS
  
  // initialize peripherals here
	LampControlInit ();
	PrintServerInit();
	SwitchMonitorInit();
	
	

  osKernelStart ();                         // start thread execution 
}
