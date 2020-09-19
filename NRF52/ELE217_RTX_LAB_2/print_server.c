#include "nrfx_uart.h"
#include "pca10040.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PRINT_BUFFER_SIZE 128 
#define RX_PIN_NUMBER  8
#define TX_PIN_NUMBER  6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5


static nrfx_uart_t uart_inst = NRFX_UART_INSTANCE(0);

void PrintServerInit(void){
	
	nrfx_uart_config_t uart_config = NRFX_UART_DEFAULT_CONFIG;
	
	nrfx_err_t nrfx_err = nrfx_uart_init(&uart_inst, &uart_config, NULL);

	
	return ;
}
	


void PrintServerPrintf(const char *fmt, ...) 
{ 
			uint8_t buff[PRINT_BUFFER_SIZE]; 
			va_list args; 
				
			va_start(args, fmt); 
			vsnprintf((char *)buff, PRINT_BUFFER_SIZE, fmt, args); 
			va_end(args); 
					
				for (uint32_t i = 0; i < strlen((char *)buff); i++) 
							{ nrfx_err_t nrfx_err = nrfx_uart_tx(&uart_inst, (const uint8_t *)&buff[i], 1); 
							if (nrfx_err != NRFX_SUCCESS) { return; } 
							} 
							
}

