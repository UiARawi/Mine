#ifndef INCLUSION_GUARD_LAMP_CONTROL_H
#define INCLUSION_GUARD_LAMP_CONTROL_H
// Defining some symbolic names on signals known to the lamp control module
#define SIGNAL_LED_ON 0x01
#define SIGNAL_LED_OFF 0x02

#include "cmsis_os.h"

//pre declaration
int LampControlInit (void);
void LampControl (void const *argument); 



#endif // INCLUSION_GUARD_LAMP_CONTROL_H
