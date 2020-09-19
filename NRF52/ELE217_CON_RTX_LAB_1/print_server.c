#include "nrfx_uart.h"
#include "pca10040.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cmsis_os.h"

#define BUFFER_SIZE 64 
#define RX_PIN_NUMBER  8
#define TX_PIN_NUMBER  6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5

void Printserver(void const *argu);
typedef struct{
char buffer[64];
}PRINT_BUFFER_SIZE;

osThreadId Printserver_ID;
osThreadDef(Printserver, osPriorityBelowNormal,1,0);

osMailQDef(mail_box, 16, PRINT_BUFFER_SIZE);											//define the mailbox 
osMailQId  mail_box_ID;															//define the mailbox id


static nrfx_uart_t uart_inst = NRFX_UART_INSTANCE(0);

void PrintServerInit(void){
	mail_box_ID = osMailCreate(osMailQ(mail_box), NULL);
	Printserver_ID = osThreadCreate(osThread(Printserver),(void *) NULL);
	
	nrfx_uart_config_t uart_config = NRFX_UART_DEFAULT_CONFIG;
	nrfx_err_t nrfx_err = nrfx_uart_init(&uart_inst, &uart_config, NULL);

	return ;
}
	


void PrintServerPrintf(const char *fmt, ...) 
{     PRINT_BUFFER_SIZE *PrintTX;
			PrintTX = (PRINT_BUFFER_SIZE*)osMailAlloc(mail_box_ID, osWaitForever);	
			
			va_list args; 
			va_start(args, fmt); 
			vsnprintf((char *)PrintTX->buffer, BUFFER_SIZE, fmt, args); 
			va_end(args); 
	
			osMailPut(mail_box_ID,PrintTX->buffer);

}

void Printserver(void const *argu)
{  

		osEvent evt;																	//declare an osEvent variable
		PRINT_BUFFER_SIZE *PrintRX;																//define a pointer in the mailslot format
	while(1)
{  
	evt = osMailGet(mail_box_ID, osWaitForever);     //wait until a message arrives
	if(evt.status == osEventMail)										//Check for a valid message
	{																								
	PrintRX = (PRINT_BUFFER_SIZE*)evt.value.p;			//Set the receive pointer to the mailslot
		
	nrfx_err_t nrfx_err = nrfx_uart_tx(&uart_inst, (const uint8_t *)&PrintRX->buffer, strlen((char *)PrintRX->buffer)); 
			
		
	osMailFree(mail_box_ID, PrintRX);
	}
}


}

