/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : UART Interrupt-Driven Data Transmission and Reception Application
 ******************************************************************************

 * This application did asynchronous data transmission over the USART peripheral using hardware interrupts (TXE and TC).
 *  Configuration:
 * - Word Length: 8-bit frames
 * - Parity     :  Disable
 *
 *  Functional Flow: Transmitter
 * 1. The application fills a data buffer.
 * 2. Transmission is initiated by activating TXEIE and TCIE control bits.
 * 3. The `USART_IRQHandling` function processes each byte upon the Transmit Data Register Empty (TXE) interrupt flag without blocking the CPU.
 * 4. Once `TxLen` drops to 0, TXEIE is disabled.
 * 5. The Transmission Complete (TC) flag reset the driver state to READY and triggering the user callback.
 *
 *    Functional Flow: Receiver
 * 1. The application sets up a reception buffer and specifies the expected number of bytes to receive (RxLen).
 * 2. The driver enables the Receive Data Register Not Empty Interrupt (RXNEIE).
 * 3. When the sender transmits a byte, the hardware sets the RXNE flag to 1, pausing the CPU to jump into `USART_IRQHandling`.
 * 4. The ISR reads the Data Register (DR), which  clears the RXNE flag, and saves the byte into the buffer.
 * 5. This process continues non-blocking (one byte per interrupt). Once RxLen reaches 0, RXNEIE is disabled, and the application callback
 *    is notified with a reception complete event.
 *
 ******************************************************************************
 */


#include<stdio.h>
#include<string.h>
#include "stm32f407.h"
#include <stddef.h>

int main(void)
{
    uint8_t key;
    uint8_t received;

    /* =========================
       USART1 Initialization
       ========================= */

    USART1_Init();
    USART1_GPIOInit();


    /* =========================
       Keypad Initialization
       ========================= */

    GPIO_KeypadInit();


    /* =========================
       LCD Initialization
       ========================= */

    lcd_port_initialize();
    lcd_Initizalize();


    /* =========================
       Enable USART1
       ========================= */

    USART_PeripheralControl(USART1, ENABLE);


    /* =========================
       Enable USART1 Interrupt
       ========================= */

    USART_IRQInterruptConfig(IRQ_NO_USART1, ENABLE);

    USART_IRQPriorityConfig(IRQ_NO_USART1, 15);


    /* =========================
       Start USART RX
       ========================= */

    TxRx_StartReceive();


    while(1)
    {
        /* =====================
           Check keypad
           ===================== */

        key = Keypad_GetKey();

        if(key != 0)
        {
            TxRx_SendByte(key);
        }


        /* =====================
           Check received data
           ===================== */

        if(TxRx_DataAvailable())
        {
            received = TxRx_GetReceivedByte();

            /* Display received character on LCD */
            LCD_data(received);

            /* Prepare USART RX for next character */
            TxRx_StartReceive();
        }
    }
}



