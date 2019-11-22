#include "main.h"
#include "usb_device.h"
#include "gpio.h"


UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);





int main(void) {

    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USB_DEVICE_Init();


    while (1) {

    }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}



static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO output pins default levels */
  HAL_GPIO_WritePin(ERROR_GPIO_GPIO_Port, ERROR_GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CH0_INDICATOR_PORT, CH0_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH1_INDICATOR_PORT, CH1_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH2_INDICATOR_PORT, CH2_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH3_INDICATOR_PORT, CH3_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH4_INDICATOR_PORT, CH4_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH5_INDICATOR_PORT, CH5_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH6_INDICATOR_PORT, CH6_INDICATOR_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CH7_INDICATOR_PORT, CH7_INDICATOR_PIN, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(TARGET_SELECT_0_MUX_DRIVER_PORT, TARGET_SELECT_0_MUX_DRIVER_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TARGET_SELECT_1_MUX_DRIVER_PORT, TARGET_SELECT_1_MUX_DRIVER_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TARGET_SELECT_2_MUX_DRIVER_PORT, TARGET_SELECT_2_MUX_DRIVER_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(J_NRES_DISABLE_PORT, J_NRES_DISABLE_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(HERD_RES_ALL_PORT, HERD_RES_ALL_PIN, GPIO_PIN_RESET);


  /*Configure GPIO pin : ERROR_GPIO_Pin */
  GPIO_InitStruct.Pin = ERROR_GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ERROR_GPIO_GPIO_Port, &GPIO_InitStruct);


  /*Configure GPIO pin : CH0_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH0_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH0_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH1_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH1_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH1_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH2_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH2_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH2_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH3_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH3_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH3_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH4_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH4_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH4_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH5_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH5_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH5_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH6_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH6_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH6_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : CH7_INDICATOR_PIN */
  GPIO_InitStruct.Pin = CH7_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CH7_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : TARGET_SELECT_0_MUX_DRIVER_PIN */
  GPIO_InitStruct.Pin = TARGET_SELECT_0_MUX_DRIVER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TARGET_SELECT_0_MUX_DRIVER_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : TARGET_SELECT_1_MUX_DRIVER_PIN */
  GPIO_InitStruct.Pin = TARGET_SELECT_1_MUX_DRIVER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TARGET_SELECT_1_MUX_DRIVER_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : TARGET_SELECT_2_MUX_DRIVER_PIN */
  GPIO_InitStruct.Pin = TARGET_SELECT_2_MUX_DRIVER_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TARGET_SELECT_2_MUX_DRIVER_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_POWER_INDICATOR_PIN */
  GPIO_InitStruct.Pin = USB_POWER_INDICATOR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP; //TODO - usunąć w wersji na gotową płytkę
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_POWER_INDICATOR_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin : TARGET_SELECT_MAN_SW_PIN */
  GPIO_InitStruct.Pin = TARGET_SELECT_MAN_SW_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TARGET_SELECT_MAN_SW_PORT, &GPIO_InitStruct);
  /*Configure GPIO pin : TARGET_RESET_MAN_SW_PIN */
  GPIO_InitStruct.Pin = TARGET_RESET_MAN_SW_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TARGET_RESET_MAN_SW_PORT, &GPIO_InitStruct);

  // manage interrupt handlers here

}




void Error_Handler(void)
{
  HAL_GPIO_WritePin(ERROR_GPIO_GPIO_Port, ERROR_GPIO_Pin, GPIO_PIN_RESET);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
