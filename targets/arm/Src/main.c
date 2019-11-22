#include "main.h"
#include "usb_device.h"
#include "gpio.h"
#include "uart.h"
#include "clock.h"
#include <stdbool.h>




void Error_Handler(void);


int main(void) {
    GPIO_Init();
    if(SystemClock_Config()== false) Error_Handler();
    if(USART1_UART_Init() == false) Error_Handler();
    USB_DEVICE_Init();


    while (1) {

    }
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
