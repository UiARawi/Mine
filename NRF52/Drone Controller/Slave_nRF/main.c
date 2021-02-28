/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"  
#include "print_server.h" 
#include "switch_monitor.h" 
#include "Twi_fx.h"
#include "SPI.h"

int main(void)
{
	osKernelInitialize(); // Initialize CMSIS-RTOS

	PrintServerInit();
	SwitchMonitorInit();
	twi_init ();
	twiSetRegisters ();
	ExtCBInit ();
	SpiInit(); 
	
	osKernelStart(); // Start thread execution
}
