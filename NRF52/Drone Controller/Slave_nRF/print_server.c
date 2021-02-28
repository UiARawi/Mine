#include "nrfx_uart.h"
#include "pca10040.h"
#include "print_server.h"
#include <stdarg.h>
#include <string.h>
#include "cmsis_os.h" 
#define PRINT_BUFFER_SIZE 64

//difeine a que and id of it
osMailQId mail_box_id;
osMailQDef(mail_queue, 1, mail_format_t);//may also use a struckt mail_format_t

/*threads*/
osThreadId PrintServer_id; 
osThreadDef (PrintServer, osPriorityNormal, 1, 0); 														// thread object

//definerer en ny global variabel uart instans
static nrfx_uart_t uart_inst = NRFX_UART_INSTANCE(0);

bool PrintServerInit (void)
{	
	//makes a que
	mail_box_id = osMailCreate(osMailQ(mail_queue), NULL);
	/*Creat trhred*/
  PrintServer_id = osThreadCreate (osThread(PrintServer),NULL);  
	
		//Deretter settes UART pinnene i konfigurasjon med makroer (TX_PIN_NUMBER, RX_PIN_NUMBER, CTS_PIN_NUMBER, RTS_PIN_NUMBER) fra filen pca10040.h 
		nrfx_uart_config_t uart_config = NRFX_UART_DEFAULT_CONFIG;
	   uart_config.pseltxd = TX_PIN_NUMBER;                                                                                \
     uart_config.pselrxd = RX_PIN_NUMBER; 
	//	uart_config.hwfc = UART_CONFIG_HWFC_Disabled;
	   
		//initalisering av uarten
			nrfx_err_t nrfx_err = nrfx_uart_init(&uart_inst, &uart_config, NULL);
			return nrfx_err;	
}	

void PrintServerPrintf(const char *fmt, ...)
{
	//allokate memory block
	mail_format_t *mail = osMailAlloc(mail_box_id, osWaitForever);
	//fill block
	
	va_list args;	
	va_start(args, fmt);
	vsnprintf((char *)mail->some_data, PRINT_BUFFER_SIZE, fmt, args);
	va_end(args);	
	
	//strcpy(mail->some_data, fmt);
	//send block
	osMailPut(mail_box_id, mail->some_data);
	
}
void PrintServer(void const *argument)
{
  while (1) 
		{	
				//wait to recive mail
				osEvent my_event = osMailGet(mail_box_id, osWaitForever);
				//convert pointer to formate
				mail_format_t *mail = (mail_format_t*)my_event.value.p;
				//write to uart 
				nrfx_uart_tx(&uart_inst, (const uint8_t*)&mail->some_data, strlen((char*)mail));
				//free memory block
				osMailFree(mail_box_id, mail);					
    }  
}
