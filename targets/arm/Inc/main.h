/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/


#define ERROR_GPIO_GPIO_Port GPIOC
#define CH0_INDICATOR_PORT GPIOB
#define CH1_INDICATOR_PORT GPIOB
#define CH2_INDICATOR_PORT GPIOB
#define CH3_INDICATOR_PORT GPIOB
#define CH4_INDICATOR_PORT GPIOB
#define CH5_INDICATOR_PORT GPIOA
#define CH6_INDICATOR_PORT GPIOA
#define CH7_INDICATOR_PORT GPIOA
#define TARGET_SELECT_0_MUX_DRIVER_PORT GPIOA
#define TARGET_SELECT_1_MUX_DRIVER_PORT GPIOA
#define TARGET_SELECT_2_MUX_DRIVER_PORT GPIOA
#define TARGET_SELECT_MAN_SW_PORT GPIOB
#define TARGET_RESET_MAN_SW_PORT GPIOB
#define J_NRES_DISABLE_PORT GPIOA
#define HERD_RES_ALL_PORT GPIOA
#define USB_POWER_INDICATOR_PORT GPIOA


#define ERROR_GPIO_Pin GPIO_PIN_13
#define CH0_INDICATOR_PIN GPIO_PIN_12
#define CH1_INDICATOR_PIN GPIO_PIN_11
#define CH2_INDICATOR_PIN GPIO_PIN_10
#define CH3_INDICATOR_PIN GPIO_PIN_1
#define CH4_INDICATOR_PIN GPIO_PIN_0
#define CH5_INDICATOR_PIN GPIO_PIN_7
#define CH6_INDICATOR_PIN GPIO_PIN_4
#define TARGET_SELECT_0_MUX_DRIVER_PIN GPIO_PIN_0
#define TARGET_SELECT_1_MUX_DRIVER_PIN GPIO_PIN_1
#define TARGET_SELECT_2_MUX_DRIVER_PIN GPIO_PIN_2
#define TARGET_SELECT_MAN_SW_PIN GPIO_PIN_5
#define TARGET_RESET_MAN_SW_PIN GPIO_PIN_6
#define J_NRES_DISABLE_PIN GPIO_PIN_6
#define HERD_RES_ALL_PIN GPIO_PIN_5
#define USB_POWER_INDICATOR_PIN GPIO_PIN_8


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
