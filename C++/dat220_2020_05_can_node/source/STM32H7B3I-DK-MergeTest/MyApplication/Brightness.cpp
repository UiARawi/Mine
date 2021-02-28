/*
 * Brightness.cpp
 *
 *  Created on: 15. nov. 2020
 *      Author: mohasa18
 */

#include "cmsis_os.h"
#include "brightness.hpp"
#include "main.h"

osMessageQDef(Bright, 5, int);
osMessageQId setBrightnessQId;
osThreadId setBrightnessId;

void brightnessInit()
{
	osThreadDef(brightnessThread, brightnessTask, osPriorityNormal, 0, 256);
	setBrightnessId = osThreadCreate(osThread(brightnessThread), NULL);

	setBrightnessQId = osMessageCreate(osMessageQ(Bright), NULL);
}

// simulerer en PWM signal med osDelay
void brightnessTask(void const* argument)
{
	osEvent event;
	int delay = 10;
	int on_time = 10;
	int off_time = 0;

	for(;;){

	  event = osMessageGet(setBrightnessQId, 0);
	  if( event.status == osEventMessage)
	  {
		  off_time  = delay - (int)event.value.p/10;
		  on_time = delay - off_time;
	  }

	  if(on_time == 0)
		  off_time = 15;

	  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_RESET);
	  osDelay(off_time);
	  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);
	  osDelay(on_time);

	}
}


