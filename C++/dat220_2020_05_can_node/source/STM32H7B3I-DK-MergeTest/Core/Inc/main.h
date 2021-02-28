/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#define SDRAM_BANK_ADDR                 ((uint32_t)0xD0000000) // 4x64 MB
#define SDRAM_BANK1_ADDR                 ((uint32_t)0C0000000) // 4x64 MB
#define REFRESH_COUNT                    ((uint32_t)0x0603)   /* SDRAM refresh counter (100Mhz SD clock) */

#define IS42S16800J_TIMEOUT             ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1               0x0000U
#define SDRAM_MODEREG_BURST_LENGTH_2               0x0001U
#define SDRAM_MODEREG_BURST_LENGTH_4               0x0002U
#define SDRAM_MODEREG_BURST_LENGTH_8               0x0004U
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL        0x0000U
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED       0x0008U
#define SDRAM_MODEREG_CAS_LATENCY_2                0x0020U
#define SDRAM_MODEREG_CAS_LATENCY_3                0x0030U
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD      0x0000U
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED   0x0000U
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE       0x0200U


#define CAN_ID_102 0x102
#define CAN_ID_154 0x154
#define CAN_ID_232 0x232
#define CAN_ID_266 0x266
#define CAN_ID_382 0x382
#define CAN_ID_3D2 0x3D2
#define CAN_ID_562 0x562


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FMC_SDNCAS_Pin GPIO_PIN_15
#define FMC_SDNCAS_GPIO_Port GPIOG
#define FMC_NBL0_Pin GPIO_PIN_0
#define FMC_NBL0_GPIO_Port GPIOE
#define FMC_D3_Pin GPIO_PIN_1
#define FMC_D3_GPIO_Port GPIOD
#define FMC_NBL1_Pin GPIO_PIN_1
#define FMC_NBL1_GPIO_Port GPIOE
#define FMC_D2_Pin GPIO_PIN_0
#define FMC_D2_GPIO_Port GPIOD
#define FMC_SDCLK_Pin GPIO_PIN_8
#define FMC_SDCLK_GPIO_Port GPIOG
#define FMC_A1_Pin GPIO_PIN_1
#define FMC_A1_GPIO_Port GPIOF
#define FMC_A0_Pin GPIO_PIN_0
#define FMC_A0_GPIO_Port GPIOF
#define FMC_BA1_Pin GPIO_PIN_5
#define FMC_BA1_GPIO_Port GPIOG
#define FMC_A2_Pin GPIO_PIN_2
#define FMC_A2_GPIO_Port GPIOF
#define FMC_A4_Pin GPIO_PIN_4
#define FMC_A4_GPIO_Port GPIOF
#define FMC_BA0_Pin GPIO_PIN_4
#define FMC_BA0_GPIO_Port GPIOG
#define FMC_D0_Pin GPIO_PIN_14
#define FMC_D0_GPIO_Port GPIOD
#define FMC_D1_Pin GPIO_PIN_15
#define FMC_D1_GPIO_Port GPIOD
#define FMC_A3_Pin GPIO_PIN_3
#define FMC_A3_GPIO_Port GPIOF
#define FMC_A5_Pin GPIO_PIN_5
#define FMC_A5_GPIO_Port GPIOF
#define FMC_D9_Pin GPIO_PIN_12
#define FMC_D9_GPIO_Port GPIOE
#define FMC_D13_Pin GPIO_PIN_8
#define FMC_D13_GPIO_Port GPIOD
#define FMC_D15_Pin GPIO_PIN_10
#define FMC_A7_Pin GPIO_PIN_13
#define FMC_A7_GPIO_Port GPIOF
#define FMC_D4_Pin GPIO_PIN_7
#define FMC_D4_GPIO_Port GPIOE
#define FMC_D10_Pin GPIO_PIN_13
#define FMC_D10_GPIO_Port GPIOE
#define FMC_SDNE1_Pin GPIO_PIN_6
#define FMC_SDNE1_GPIO_Port GPIOH
#define FMC_SDNRAS_Pin GPIO_PIN_11
#define FMC_SDNRAS_GPIO_Port GPIOF
#define FMC_A9_Pin GPIO_PIN_15
#define FMC_A9_GPIO_Port GPIOF
#define FMC_D11_Pin GPIO_PIN_14
#define FMC_D11_GPIO_Port GPIOE
#define FMC_D7_Pin GPIO_PIN_10
#define FMC_D7_GPIO_Port GPIOE
#define FMC_D14_Pin GPIO_PIN_9
#define FMC_D14_GPIO_Port GPIOD
#define FMC_SDNWE_Pin GPIO_PIN_5
#define FMC_SDNWE_GPIO_Port GPIOH
#define FMC_A8_Pin GPIO_PIN_14
#define FMC_A8_GPIO_Port GPIOF
#define FMC_A11_Pin GPIO_PIN_1
#define FMC_A11_GPIO_Port GPIOG
#define FMC_D6_Pin GPIO_PIN_9
#define FMC_D6_GPIO_Port GPIOE
#define FMC_D12_Pin GPIO_PIN_15
#define FMC_D12_GPIO_Port GPIOE
#define FMC_D15_GPIO_Port GPIOD
#define FMC_A6_Pin GPIO_PIN_12
#define FMC_A6_GPIO_Port GPIOF
#define FMC_A10_Pin GPIO_PIN_0
#define FMC_A10_GPIO_Port GPIOG
#define FMC_D5_Pin GPIO_PIN_8
#define FMC_D5_GPIO_Port GPIOE
#define FMC_D8_Pin GPIO_PIN_11
#define FMC_D8_GPIO_Port GPIOE
#define FMC_SDCKE1_Pin GPIO_PIN_7
#define FMC_SDCKE1_GPIO_Port GPIOH


#define I2S6_SDO_Pin_Pin GPIO_PIN_14
#define I2S6_SDO_Pin_GPIO_Port GPIOG
#define I2S6_SDI_Pin_Pin GPIO_PIN_12
#define I2S6_SDI_Pin_GPIO_Port GPIOG
#define I2S6_WS_Pin_Pin GPIO_PIN_0
#define I2S6_WS_Pin_GPIO_Port GPIOA
#define I2S6_MCK_Pin_Pin GPIO_PIN_3
#define I2S6_MCK_Pin_GPIO_Port GPIOA

#define I2S_CK_Pin_Pin GPIO_PIN_13
#define I2S_CK_Pin_GPIO_Port GPIOG

/*OCTOSPI */

#define OCSPI_IO4_Pin GPIO_PIN_1
#define OCSPI_IO4_GPIO_Port GPIOC

#define OCSPI_IO5_Pin GPIO_PIN_3
#define OCSPI_IO5_GPIO_Port GPIOH

#define OCSPI_IO6_Pin GPIO_PIN_9
#define OCSPI_IO6_GPIO_Port GPIOG

#define OCSPI_IO7_Pin GPIO_PIN_7
#define OCSPI_IO7_GPIO_Port GPIOD

#define OCSPI_NCS_Pin GPIO_PIN_6
#define OCSPI_NCS_GPIO_Port GPIOG


#define OCSPI_DQS_Pin GPIO_PIN_5
#define OCSPI_DQS_GPIO_Port GPIOC

#define OCSPI_CLK_Pin GPIO_PIN_2
#define OCSPI_CLK_GPIO_Port GPIOB


#define SDIO1_D2_Pin_Pin GPIO_PIN_10
#define SDIO1_D2_Pin_GPIO_Port GPIOC
#define SDIO1_CMD_Pin_Pin GPIO_PIN_2
#define SDIO1_CMD_Pin_GPIO_Port GPIOD
#define SDIO1_CK_Pin_Pin GPIO_PIN_12
#define SDIO1_CK_Pin_GPIO_Port GPIOC
#define SDIO1_D3_Pin_Pin GPIO_PIN_11
#define SDIO1_D3_Pin_GPIO_Port GPIOC
#define SDIO1_D1_Pin_Pin GPIO_PIN_9
#define SDIO1_D1_Pin_GPIO_Port GPIOC
#define SDIO1_D0_Pin_Pin GPIO_PIN_8
#define SDIO1_D0_Pin_GPIO_Port GPIOC

#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_11
#define LED3_GPIO_Port GPIOG

#define VSYNC_FREQ_Pin GPIO_PIN_15
#define VSYNC_FREQ_GPIO_Port GPIOA

#define MCU_ACTIVE_Pin GPIO_PIN_0
#define MCU_ACTIVE_GPIO_Port GPIOI

#define FDCANTX_Pin_Pin GPIO_PIN_12
#define FDCANTX_Pin_GPIO_Port GPIOA
#define FDCANRX_Pin_Pin GPIO_PIN_11
#define FDCANRX_Pin_GPIO_Port GPIOA
#define FDCAN1_STDBY_Pin GPIO_PIN_8
#define FDCAN1_STDBY_GPIO_Port GPIOH


#define RCC_OSC32_IN_Pin GPIO_PIN_14
#define RCC_OSC32_IN_GPIO_Port GPIOC
#define RCC_OSC32_OUT_Pin GPIO_PIN_15
#define RCC_OSC32_OUT_GPIO_Port GPIOC
#define RCC_MCO_Pin GPIO_PIN_8
#define RCC_MCO_GPIO_Port GPIOA
#define RCC_OSC_IN_Pin GPIO_PIN_0
#define RCC_OSC_IN_GPIO_Port GPIOH
#define RCC_OSC_OUT_Pin GPIO_PIN_1
#define RCC_OSC_OUT_GPIO_Port GPIOH

#define USARTRX_Pin_Pin GPIO_PIN_10
#define USARTRX_Pin_GPIO_Port GPIOA
#define USARTTX_Pin_Pin GPIO_PIN_9
#define USARTTX_Pin_GPIO_Port GPIOA


#define I2C4_SDA_Pin_Pin GPIO_PIN_13
#define I2C4_SDA_Pin_GPIO_Port GPIOD
#define I2C4_CL_Pin_Pin GPIO_PIN_12
#define I2C4_CL_Pin_GPIO_Port GPIOD


#define LCD_BL_CTRL_Pin GPIO_PIN_1
#define LCD_BL_CTRL_GPIO_Port GPIOA
#define LCD_ON_OFF_Pin GPIO_PIN_2
#define LCD_ON_OFF_GPIO_Port GPIOA
#define LCD_INT_Pin GPIO_PIN_2
#define LCD_INT_GPIO_Port GPIOH
#define LCD_INT_EXTI_IRQn EXTI2_IRQn

#define RENDER_TIME_Pin GPIO_PIN_14
#define RENDER_TIME_GPIO_Port GPIOB
#define FRAME_RATE_Pin GPIO_PIN_15
#define FRAME_RATE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
