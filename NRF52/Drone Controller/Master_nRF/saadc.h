#ifndef INCLUSION_GUARD_SAADC_H
#define INCLUSION_GUARD_SAADC_H
#include <cmsis_os.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "print_server.h"

#define SAMPLES_IN_BUFFER 5

void SaAdc (void const *argument);
void Saadc_Callback(nrf_drv_saadc_evt_t const * p_event);
void SaadcInit (void); 

//volatile uint8_t state = 1;
static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(0);
//static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
//static nrf_ppi_channel_t     m_ppi_channel;
//static uint32_t              m_adc_evt_counter;


#endif //INCLUSION_GUARD_SAADC_H
