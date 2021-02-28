/*
 * timer.hpp
 *
 *  Created on: Nov 10, 2020
 *      Author: mohasa18
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

/**
 * @file  timer.hpp
 *
 * @brief Header file for timer library
 *
 * @note Initialization of timer involves setting interrupt priority,
 *       so the caller of TimerInit() must have priviledged access.
 */


#include <stdbool.h>
#include <stdint.h>
#include "stm32h7xx_hal.h"

/* Definition for TIMx clock resources */
#define TIMx                           TIM2
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()


/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM2_IRQn
#define TIMx_IRQHandler                TIM2_IRQHandler

typedef struct {
	uint32_t sec;
	uint32_t microsec;
}timer_s;

/**
 * @brief Function for initializing the time service.
 *
 * This function configures the HW TIMER1 to give an interrupt
 * each seconds to be used for incrementing a seconds counter.
 */
HAL_StatusTypeDef App_timer_init();

/**
 * @brief Function for getting time since power-up/reset.
 *
 * @param[out] time_p Pointer to an object to receive the time stamp.
 */
void TimerSecondsMicrosec(timer_s *const time_p);

/**
 * @brief Function for getting time since power-up/reset.
 *
 * @retval Time in whole milliseconds returned as unsigned integer.
 */
uint32_t TimerMillisec(void);

/**
 * @brief Function for calculated elapsed time between two time stamps.
 *
 * This function calculates the elapsed interval between two time stamps.
 * Interval is returned as microseconds in signed integer. This means that
 * an interval of approx 2147 seconds will wrap and saturated maximum
 * signed value +/- 2147483647 is returned.

 * @param[in] from_time_p Pointer to a start interval time stamp.
 * @param[in] to_time_p   Pointer to a end interval time stamp.
 *
 * @retval Interval in signed microseconds.
 */
int32_t TimerIntervalMicrosec(const timer_s *const from_time_p, const timer_s *const to_time_p);






#endif /* TIMER_HPP_ */
