/*
 * timer.cpp
 *
 *  Created on: Nov 10, 2020
 *      Author: mohasa18
 */

#include <stdint.h>
#include "timer.hpp"
#include "stm32h7xx_hal_tim.h"

extern void Printf(const char *fmt, ...);
void HAL_Suspend_TIM2(void);
void HAL_Resume_TIM2(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);

/* TIM handle declaration */
TIM_HandleTypeDef    TimHandle;

/* Timer Input Capture Configuration Structure declaration */
TIM_IC_InitTypeDef     sICConfig;

/* Prescaler declaration */
__IO uint32_t uwPrescalerValue = 0;

/* Captured Values */
uint32_t               uwIC2Value1 = 0;


#define CC_HIT 1000000 // 1 second
#define MILLISEC (CC_HIT/1000)
#define MICROSEC (CC_HIT/1000000)

#define MAX_SIGNED_32BIT 0x7fffffff
#define MAX_SEC (MAX_SIGNED_32BIT/1000000)
#define MAX_MICROSEC (MAX_SIGNED_32BIT - (MAX_SEC*1000000))

extern uint32_t time_seconds;


void TimerSecondsMicrosec(timer_s *const time_p)
{
	uint32_t current_sec, current_cc;

	__disable_irq();

	if(HAL_TIM_GenerateEvent(&TimHandle,TIM_EVENTSOURCE_CC2) == HAL_OK){

		// Store the current value of the timer in the CC[2] register, by triggering the capture task
		uwIC2Value1 = TimHandle.Instance->CCR2;
		Printf("uwIC2Value1 %i : \r\n", uwIC2Value1);
		// Store locally timer state, i.e. seconds counter and content of CC[1] register
		current_sec = time_seconds;
		current_cc = uwIC2Value1;
	}

	__enable_irq();

	// Return current time in seconds and microseconds
	time_p->sec = current_sec;
	time_p->microsec = current_cc / MICROSEC;
}

uint32_t TimerMillisec(void)
{
	uint32_t current_sec, current_cc;

	__disable_irq();
	if(HAL_TIM_GenerateEvent(&TimHandle,TIM_EVENTSOURCE_CC2) == HAL_OK){

		// Store the current value of the timer in the CC[2] register, by triggering the capture task
		uwIC2Value1 = TimHandle.Instance->CCR2;
		Printf("uwIC2Value1 %i : \r\n", uwIC2Value1);
		// Store locally timer state, i.e. seconds counter and content of CC[1] register
		current_sec = time_seconds;
		current_cc = uwIC2Value1;
	}
	__enable_irq();

	// Return current time in seconds and milliseconds
	return (current_sec * 1000) + (current_cc / MILLISEC);
}

int32_t TimerIntervalMicrosec(const timer_s *const from_time_p, const timer_s *const to_time_p)
{
	const timer_s *from_p, *to_p;
	int32_t sign = 1;
	timer_s delta_time;

	if (from_time_p->sec > to_time_p->sec) {
		from_p = to_time_p;
		to_p = from_time_p;
		sign = -1;
	} else if ((from_time_p->sec == to_time_p->sec) && (from_time_p->microsec > to_time_p->microsec)) {
		from_p = to_time_p;
		to_p = from_time_p;
		sign = -1;
	} else {
		from_p = from_time_p;
		to_p = to_time_p;
	}

	delta_time.sec = to_p->sec - from_p->sec;

	if (to_p->microsec >= from_p->microsec) {
		delta_time.microsec = to_p->microsec - from_p->microsec;
	} else {
		delta_time.microsec = CC_HIT - from_p->microsec + to_p->microsec;
		if(delta_time.sec > 0){

			delta_time.sec--;
		}
	}

	if ((delta_time.sec < MAX_SEC) || ((delta_time.sec == MAX_SEC) && (delta_time.microsec <= MAX_MICROSEC))) {
		// Return signed interval in microseconds
		return ((delta_time.sec * 1000000 + delta_time.microsec) * sign);
	}

	// Return maximum signed interval +/- 2 147 483 647 microseconds
	return (MAX_SIGNED_32BIT * sign);
}

HAL_StatusTypeDef App_timer_init(){

	uint32_t              uwTimclock = 0;

	/*##-1- Configure the TIM peripheral #######################################*/
	/* -----------------------------------------------------------------------
	TIM3 input clock (TIM3CLK)  is set to APB1 clock (PCLK1)x1,
	since APB1 prescaler is equal to 1.
	TIM2CLK = PCLK1*1
	PCLK1 = HCLK/1
	=> TIM2CLK = HCLK = SystemCoreClock
	To get TIM3 counter clock at 1 MHz, the Prescaler is computed as follows:
	Prescaler = (TIM2CLK / TIM2 counter clock) - 1
	Prescaler = ((SystemCoreClock) /1 MHz) - 1
	----------------------------------------------------------------------- */

	uwTimclock = HAL_RCC_GetPCLK1Freq();

	/* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */

	uwPrescalerValue = (uint32_t)((uwTimclock / 1000000) - 1);

	/* Set TIMx instance */
	TimHandle.Instance = TIMx;

	/* Initialize TIMx peripheral as follow:
	+ Period = [(TIM2CLK) - 1]. to have a (1) s time base.
	+ Prescaler = (uwTimclock/1000000) - 1 to have a 1 MHz counter clock.
	+ ClockDivision = 0
	+ Counter direction = Up
	*/
	TimHandle.Init.Period            = (1000000 ) - 1; // 999 999
	TimHandle.Init.Prescaler         = uwPrescalerValue; // 119
	TimHandle.Init.ClockDivision     = 0;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	{

	}
	/*##-2- Configure the Input Capture channel ################################*/
	/* Configure the Input Capture of channel 2 */
	sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;
	sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sICConfig.ICPrescaler = TIM_ICPSC_DIV1;
	sICConfig.ICFilter    = 0;
	if(HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_2) != HAL_OK)
	{
	/* Configuration Error */

	}

	if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
	/* Starting Error */

	}

	return HAL_ERROR;

}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{

 if (htim->Instance == TIM2){
	  /*##-1- Enable peripheral clock #################################*/


	  /*##-2- Configure the NVIC for TIMx ########################################*/
	  /* Set the TIMx priority */
	  HAL_NVIC_SetPriority(TIMx_IRQn, 5, 0);

	  /* Enable the TIMx global Interrupt */
	  HAL_NVIC_EnableIRQ(TIMx_IRQn);

	  /* TIMx Peripheral clock enable */
	  TIMx_CLK_ENABLE();
	  /**
		* @brief  Enables or disables the TIM Capture Compare Channel x.
		* @param  TIMx to select the TIM peripheral
		* @param  Channel specifies the TIM Channel
		*          This parameter can be one of the following values:
		*            @arg TIM_CHANNEL_1: TIM Channel 1
		*            @arg TIM_CHANNEL_2: TIM Channel 2
		*            @arg TIM_CHANNEL_3: TIM Channel 3
		*            @arg TIM_CHANNEL_4: TIM Channel 4
		*            @arg TIM_CHANNEL_5: TIM Channel 5 selected
		*            @arg TIM_CHANNEL_6: TIM Channel 6 selected
		* @param  ChannelState specifies the TIM Channel CCxE bit new state.
		*          This parameter can be: TIM_CCx_ENABLE or TIM_CCx_DISABLE.
		* @retval None
		*/
	  TIM_CCxChannelCmd(TIM3,TIM_CHANNEL_2, TIM_CCx_ENABLE);
	}
}


/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM7 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_Suspend_TIM2(void)
{
  /* Disable TIM7 update Interrupt */
  __HAL_TIM_DISABLE_IT(&TimHandle, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM7 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_Resume_TIM2(void)
{
  /* Enable TIM7 Update interrupt */
  __HAL_TIM_ENABLE_IT(&TimHandle, TIM_IT_UPDATE);
}

// End of file timer.c



