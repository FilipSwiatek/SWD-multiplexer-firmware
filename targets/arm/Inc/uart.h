//
// Created by snickers on 11/22/19.
//

#ifndef PROJECT_NAME_UART_H
#define PROJECT_NAME_UART_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

bool USART1_UART_Init(void);

bool USART_PutChar(char c);

size_t USART_WriteData(const void *data, size_t dataSize);

size_t USART_WriteString(const char *string);

bool USART_GetChar(char *c);

size_t USART_ReadData(char *data, size_t maxSize);




#endif //PROJECT_NAME_UART_H
