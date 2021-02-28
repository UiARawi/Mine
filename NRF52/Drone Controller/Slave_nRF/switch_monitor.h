#ifndef INCLUSION_GUARD_SWITCH_CONTROL_H
#define INCLUSION_GUARD_SWITCH_CONTROL_H
#include <stdbool.h>
#include <nrfx_gpiote.h>

//pre declaration
#define SIGNAL_LED_ON 0x01
#define SIGNAL_LED_OFF 0x02

void ExtCBInit (void);
//void PrintServer(void const *argument);

bool SwitchMonitorInit(void);
void SwitchMonitorInterruptCB(uint32_t pin, nrf_gpiote_polarity_t polarity);
void SwitchMonitor(void const *argument);


#endif


