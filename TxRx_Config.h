/* TxRx_Config.h */

#ifndef TXRX_CONFIG_H_
#define TXRX_CONFIG_H_

#include<stdio.h>
#include<string.h>
#include "stm32f407.h"
#include <stddef.h>

/* UART Configuration */
void USART1_Init(void);
void USART1_GPIOInit(void);

/* Keypad Configuration */
void GPIO_KeypadInit(void);

void delay(uint32_t i);

uint8_t Keypad_GetKey(void);
uint8_t TxRx_SendByte(uint8_t data);

/* LCD Configuration */
void lcd_port_initialize(void);
void lcd_Initizalize(void);
void LCD_command(unsigned char command);
void LCD_data(char data);

/* Other functions */
void TxRx_StartReceive(void);
uint8_t TxRx_GetReceivedByte(void);
uint8_t TxRx_DataAvailable(void);
uint8_t Keypad_GetKeyRaw(void);

#endif /* TXRX_CONFIG_H_ */
