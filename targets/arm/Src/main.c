#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "gpio.h"
#include "uart.h"
#include "clock.h"
#include "cli.h"

uint8_t currentTarget = 0;


// handler błędu (nie mylić z hardfaultem)
void Error_Handler(void);
// cosekundowe mruganie diodą
static void ErrorDiodeBlinkingProc();
static bool switchTarget(uint8_t targetNo);
void targetTest(void);
void delay_ms(uint32_t ms);
// paraller reset control
static void allTargetsResetPush(void);
static void allTargetsResetRelease(void);
static void allTargetsResetPushAndRelease(void);

void onResetAllCommand(const char* arg);
void onSelectTargetCommand(const char* arg);
void onHelpCommand(const char* arg);

CLI_CommandItem resetAllCommand = {
        .commandName = "reset_all",
        .callback = onResetAllCommand,
        .description = "This command reset targets in ways specified by argument:\n\r "
                       "set - sets reset - as released button\n\r "
                       "clear - as pushed reset button.\n\r"
                       "If you leave argument pole empty, there will be a 20ms pulse set-clear-set.\n\r"
                       "Syntax: reset_all [set/clear/]\n\r"
};

CLI_CommandItem selectTargetCommand = {
        .commandName = "select",
        .callback = onSelectTargetCommand,
        .description = "This command  selects target.\n\r Syntax is: select [target No]\n\r"
};

CLI_CommandItem helpCommand = {
        .commandName = "help",
        .callback = onHelpCommand,
        .description = "This command shows help\n\r"
};

int main(void) {
    HAL_Init();
    GPIO_Init();
    if(SystemClock_Config() == false) Error_Handler();
    if(USART1_UART_Init() == false) Error_Handler();
    if(USB_DEVICE_Init() == false) Error_Handler();
    CLI_AddCommand(&resetAllCommand);
    CLI_AddCommand(&selectTargetCommand);
    CLI_AddCommand(&helpCommand);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (1) {
        USB_Proc(); // potrzebne do optymalizacji wysyłu danych przez USB (zbieranie danych w większe pakiety - coś na wzór algorytmu Nagle'a)
        CLI_Proc(); // porces CLI
        ErrorDiodeBlinkingProc(); // kontrola działąnia backgroundu
        //targetTest();
    }
#pragma clang diagnostic pop

}


void Error_Handler(void){
    HAL_GPIO_WritePin(ERROR_GPIO_GPIO_Port, ERROR_GPIO_Pin, GPIO_PIN_RESET);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1);
#pragma clang diagnostic pop
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
        default:
            break;
    }

    currentTarget = targetNo;

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

void onResetAllCommand(const char* arg){
    if(!strcmp(arg, "set")){
        printStrToOutputs("OK\n\r");
        allTargetsResetRelease();
    }else if(!strcmp(arg, "clear")){
        printStrToOutputs("OK\n\r");
        allTargetsResetPush();
    }else if(!strcmp(arg, "")){
        printStrToOutputs("OK\n\r");
        allTargetsResetPushAndRelease();
    }else{
        printStrToOutputs("ERR\n\r");
    }


};

void onSelectTargetCommand(const char* arg){
    uint32_t targetNo = atoi(arg);
    if(targetNo < 8 ){
        switchTarget(targetNo);
        printStrToOutputs("OK\n\r");
    }else{
        printStrToOutputs("ERR\n\r");
    }
}

void onHelpCommand(const char* arg){
    (void)arg;
    CLI_PrintAllCommands();
}

void delay_ms(uint32_t ms){
        uint32_t previousTick = HAL_GetTick();
        while(previousTick + ms > HAL_GetTick());
}

static void allTargetsResetPush(void){
    HAL_GPIO_WritePin(J_NRES_DISABLE_PORT, J_NRES_DISABLE_PIN,GPIO_PIN_SET);
    delay_ms(5); // 5 ms delay
    HAL_GPIO_WritePin(HERD_RES_ALL_PORT, HERD_RES_ALL_PIN, GPIO_PIN_SET);
}
static void allTargetsResetRelease(void){
    HAL_GPIO_WritePin(HERD_RES_ALL_PORT, HERD_RES_ALL_PIN, GPIO_PIN_RESET);
    delay_ms(5);
    HAL_GPIO_WritePin(J_NRES_DISABLE_PORT, J_NRES_DISABLE_PIN,GPIO_PIN_RESET);

}

static void allTargetsResetPushAndRelease(void){
    allTargetsResetPush();
    delay_ms(20);
    allTargetsResetRelease();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    switch(GPIO_Pin){
        case TARGET_SELECT_MAN_SW_PIN:
            currentTarget = (currentTarget+1)%8;
            switchTarget(currentTarget);
            break;
        case TARGET_RESET_MAN_SW_PIN:
            allTargetsResetPushAndRelease();
            break;
        case USB_POWER_INDICATOR_PIN:
            if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(USB_POWER_INDICATOR_PORT, USB_POWER_INDICATOR_PIN)){
                // turn off DP pullup
                HAL_GPIO_WritePin(USB_PULLUP_PORT, USB_PULLUP_PIN, GPIO_PIN_RESET);
            }else{
                // turn on DP pullup
                HAL_GPIO_WritePin(USB_PULLUP_PORT, USB_PULLUP_PIN, GPIO_PIN_SET);
            }
            break;
        default:
            break;
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