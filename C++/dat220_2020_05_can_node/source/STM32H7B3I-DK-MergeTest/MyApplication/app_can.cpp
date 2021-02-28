/*
 * app_can.cpp
 *
 *  Created on: 6. nov. 2020
 *      Author: mohasa18
 */


/** @file app_can.c
 *  @brief TBD.
 *
 *  TBD.
 */

#include <CANClass.hpp>
#include "main.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"

#include "app_can.hpp"

extern CAN can;

typedef struct {
  uint16_t id;
  uint8_t msg_length;
  uint8_t msg[8];
} AppCanMsg_t;

/* Pointer to FDCAN handle used by this application */
FDCAN_HandleTypeDef *can_handle_p;

void AppCanInit(FDCAN_HandleTypeDef *hfdcan)
{
	if (hfdcan == NULL) {

	}
	can_handle_p = hfdcan;
	if (__HAL_RCC_FDCAN_IS_CLK_DISABLED()) {

	}
	if (__HAL_RCC_FDCAN_IS_CLK_SLEEP_ENABLED()) {

	}
	/* Turn OFF CAN driver standby */
	HAL_GPIO_WritePin(FDCAN1_STDBY_GPIO_Port, FDCAN1_STDBY_Pin, GPIO_PIN_RESET);

	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(can_handle_p) != HAL_OK)
	{

	}
	if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {

	}
	if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) {

	}
}

/**
  * @brief  Rx FIFO 0 callback.
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  RxFifo0ITs indicates which Rx FIFO 0 interrupts are signaled.
  *         This parameter can be any combination of @arg FDCAN_Rx_Fifo0_Interrupts.
  * @retval None
  */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{

	const uint8_t DLC_TO_MSG_SIZE[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64}; /* Data Length Code (DLC) to message size */
	FDCAN_RxHeaderTypeDef rx_hdr;

	AppCanMsg_t rx_msg;

	if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO0))
		{
			/* Retrieve Rx messages from RX FIFO0 */
			if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_hdr, rx_msg.msg) == HAL_OK) {

				rx_msg.id = rx_hdr.Identifier;
				rx_msg.msg_length = DLC_TO_MSG_SIZE[(rx_hdr.DataLength >> 16)];

				can.push_back(new CANData(rx_msg.id, rx_msg.msg_length, rx_msg.msg));
			}
		}

		if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {

		}

	}
}
/**
  * @brief  Rx FIFO 1 callback.
  * @param  hfdcan pointer to an FDCAN_HandleTypeDef structure that contains
  *         the configuration information for the specified FDCAN.
  * @param  RxFifo1ITs indicates which Rx FIFO 1 interrupts are signaled.
  *         This parameter can be any combination of @arg FDCAN_Rx_Fifo1_Interrupts.
  * @retval None
  */
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{

	const uint8_t DLC_TO_MSG_SIZE[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64}; /* Data Length Code (DLC) to message size */
	FDCAN_RxHeaderTypeDef rx_hdr;

	AppCanMsg_t rx_msg;

	if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET){
	while (HAL_FDCAN_GetRxFifoFillLevel(hfdcan, FDCAN_RX_FIFO1))
	{
		/* Retrieve Rx messages from RX FIFO1 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rx_hdr, rx_msg.msg) == HAL_OK) {

			rx_msg.id = rx_hdr.Identifier;
			rx_msg.msg_length = DLC_TO_MSG_SIZE[(rx_hdr.DataLength >> 16)];

			can.push_back(new CANData(rx_msg.id, rx_msg.msg_length, rx_msg.msg));
		}
	}
	}
	if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) {

	}

}


/* End of file app_can.c */


