#ifndef INCLUSION_GUARD_PRINT_SERVER_H
#define INCLUSION_GUARD_PRINT_SERVER_H

#include <stdbool.h>
#include <stdint.h>



//pre declaration
#define A_TYPE_SIZE 64

typedef struct {
uint8_t  some_data[A_TYPE_SIZE];
} mail_format_t;

bool PrintServerInit (void);
void PrintServerPrintf (const char* fmt, ...);
void PrintServer(void const *argument);


#endif
