//
// Created by snickers on 11/22/19.
//
#include "stm32f1xx_hal.h"
#include "gpio.h"

void GPIO_Init(void)
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