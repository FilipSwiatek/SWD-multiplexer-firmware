//
// Created by snickers on 11/22/19.
//

#include "uart.h"
#include "stm32f1xx_hal.h"
#include "ring_buffer.h"
#include "core.h"
#include <string.h>

// UART transmit buffer descriptor
static RingBuffer USART_RingBuffer_Tx;
// UART transmit buffer memory pool
static char RingBufferData_Tx[2048];

// UART receive buffer descriptor
static RingBuffer USART_RingBuffer_Rx;
// UART receive buffer memory pool
static char RingBufferData_Rx[2048];


UART_HandleTypeDef huart1;

bool USART1_UART_Init(void) {

    // initialize ring buffers
    RingBuffer_Init(&USART_RingBuffer_Tx, RingBufferData_Tx, sizeof(RingBufferData_Tx));
    RingBuffer_Init(&USART_RingBuffer_Rx, RingBufferData_Rx, sizeof(RingBufferData_Rx));

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        return false;
    }
    /* Enable the USART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);

    return true;
}


// UART Interrupt Service Routine (ISR)
        void USART1_IRQHandler(void){

    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE)) {
        // the RXNE interrupt has occurred
        if (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE)) {
            // the RXNE interrupt is enabled
            RingBuffer_PutChar(&USART_RingBuffer_Rx, (char)(USART1->DR));
        }
    }

    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TXE)) {
        // the TXE interrupt has occurred
        if (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_TXE)) {
            // the TXE interrupt is enabled
            if(!RingBuffer_IsEmpty(&USART_RingBuffer_Tx)){
                //TX RingBuffer is not empty;

                //read char from UART_RingBuffer_Tx and send it via UART
                RingBuffer_GetChar(&USART_RingBuffer_Tx, (char*)&(USART1->DR));
            }else{
                //TX RingBuffer is empty;
                __HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
            }
        }
    }
}

bool USART_PutChar(char c){
    //returns effect of writing char intoTx buffer;
    bool result = RingBuffer_PutChar(&USART_RingBuffer_Tx, c);
    if(result){
        __HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    }
    return result;
}


size_t USART_WriteData(const void *data, size_t dataSize){
    uint8_t* data2Buff = (uint8_t*)data;
    bool isWriteCorrect = false;
    uint16_t writeSize = 0;
    for(size_t i =  0;  i <  dataSize; i++){
        CORE_EnterCriticalSection();
        isWriteCorrect = RingBuffer_PutChar(&USART_RingBuffer_Tx, *(data2Buff + i));
        CORE_ExitCriticalSection();
        if(isWriteCorrect){
            writeSize++;
        }
    }
    // enable tx interrupt
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    return writeSize;
}


size_t USART_WriteString(const char *string){
    size_t length = strlen(string);
    return USART_WriteData((void*)string, length);
}


bool USART_GetChar(char *c){
    CORE_EnterCriticalSection();
    bool result = RingBuffer_GetChar(&USART_RingBuffer_Rx , c);
    CORE_ExitCriticalSection();
    return result;
}


size_t USART_ReadData(char* data, size_t maxSize){
    size_t i;
    bool isReadCorrect = false;
    uint16_t readSize = 0;
    for(i = 0; i < maxSize ; i++){
        //if something went wrong
        CORE_EnterCriticalSection();
        isReadCorrect = RingBuffer_GetChar(&USART_RingBuffer_Rx, data+i);
        CORE_ExitCriticalSection();
        if(isReadCorrect){
            readSize++;
        }
    }
    return ++i;
}


