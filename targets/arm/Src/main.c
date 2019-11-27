#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "gpio.h"
#include "uart.h"
#include "clock.h"
#include <stdbool.h>

// handler błędu (nie mylić z hardfaultem)
void Error_Handler(void);
// cosekundowe mruganie diodą
static void ErrorDiodeBlinkingProc();
static bool switchTarget(uint8_t targetNo);
void targetTest(void);


int main(void) {
    HAL_Init();
    GPIO_Init();
    if(SystemClock_Config() == false) Error_Handler();
    if(USART1_UART_Init() == false) Error_Handler();
    if(USB_DEVICE_Init() == false) Error_Handler();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (1) {
        USB_Proc(); // potrzebne do optymalizacji wysyłu danych przez USB (zbieranie danych w większe pakiety - coś na wzór algorytmu Nagle'a)
        ErrorDiodeBlinkingProc(); // kontrola działąnia backgroundu
        targetTest();
    }
#pragma clang diagnostic pop

}


void Error_Handler(void){
    HAL_GPIO_WritePin(ERROR_GPIO_GPIO_Port, ERROR_GPIO_Pin, GPIO_PIN_RESET);
    while(1);
}

static void ErrorDiodeBlinkingProc(){
    static uint32_t previousTick;
    if(HAL_GetTick() - previousTick > 1000){
        previousTick = HAL_GetTick();
        HAL_GPIO_TogglePin(ERROR_GPIO_GPIO_Port, ERROR_GPIO_Pin);
    }
}

static bool switchTarget(uint8_t targetNo){
    if(targetNo > 7){
        return false;
    }

    if(targetNo & (1U<<0U)){
        HAL_GPIO_WritePin(TARGET_SELECT_0_MUX_DRIVER_PORT, TARGET_SELECT_0_MUX_DRIVER_PIN, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(TARGET_SELECT_0_MUX_DRIVER_PORT, TARGET_SELECT_0_MUX_DRIVER_PIN, GPIO_PIN_RESET);
    }

    if(targetNo & (1U<<1U)){
        HAL_GPIO_WritePin(TARGET_SELECT_1_MUX_DRIVER_PORT, TARGET_SELECT_1_MUX_DRIVER_PIN, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(TARGET_SELECT_1_MUX_DRIVER_PORT, TARGET_SELECT_1_MUX_DRIVER_PIN, GPIO_PIN_RESET);
    }

    if(targetNo & (1U<<2U)){
        HAL_GPIO_WritePin(TARGET_SELECT_2_MUX_DRIVER_PORT, TARGET_SELECT_2_MUX_DRIVER_PIN, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(TARGET_SELECT_2_MUX_DRIVER_PORT, TARGET_SELECT_2_MUX_DRIVER_PIN, GPIO_PIN_RESET);
    }

    // turning off channel indicators
    HAL_GPIO_WritePin(CH0_INDICATOR_PORT, CH0_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH1_INDICATOR_PORT, CH1_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH2_INDICATOR_PORT, CH2_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH3_INDICATOR_PORT, CH3_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH4_INDICATOR_PORT, CH4_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH5_INDICATOR_PORT, CH5_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH6_INDICATOR_PORT, CH6_INDICATOR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CH7_INDICATOR_PORT, CH7_INDICATOR_PIN, GPIO_PIN_RESET);

    switch(targetNo){
        case 0:
            HAL_GPIO_WritePin(CH0_INDICATOR_PORT, CH0_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(CH1_INDICATOR_PORT, CH1_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(CH2_INDICATOR_PORT, CH2_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(CH3_INDICATOR_PORT, CH3_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(CH4_INDICATOR_PORT, CH4_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(CH5_INDICATOR_PORT, CH5_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(CH6_INDICATOR_PORT, CH6_INDICATOR_PIN, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(CH7_INDICATOR_PORT, CH7_INDICATOR_PIN, GPIO_PIN_SET);
            break;
    }

       return true;
}

void targetTest(void){
    static uint32_t previousTick;
    static uint8_t target;

    if(HAL_GetTick() - previousTick > 1000){
        previousTick = HAL_GetTick();
        //mięsko
        switchTarget(target);
        target++;
        target = target % 8;
    }
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

}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
#endif  //USE_FULL_ASSERT