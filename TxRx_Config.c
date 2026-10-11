/* TxRx_Config.c */

 /* LCD Interface
 *
 * LCD Control Pins:
 * RS -> PC0 *
 * RW -> PC1 *
 * EN -> PC2 *
 *
 * LCD Data Pins:
 * 	D0 -> PD0 *
 * 	D1 -> PD1 *
 * 	D2 -> PD2 *
 * 	D3 -> PD3 *
 *  D4 -> PD4 *
 *  D5 -> PD5 *
 *  D6 -> PD6 *
 *  D7 -> PD7
 *  */


#include "TxRx_Config.h"

USART_Handle_t USART_Handle;
static uint8_t txData;

/* RX data buffer */
static uint8_t rxData;

/* RX complete flag */
static uint8_t rxComplete = 0;

#define RS  GPIO_PIN_NO_0     // PC0
#define RW  GPIO_PIN_NO_1     // PC1
#define EN  GPIO_PIN_NO_2     // PC2


void delay(uint32_t i)
{
    for(; i > 0; i--)
    {
        for(uint32_t m = 0; m < 3198; m++);
    }
}


void USART1_Init(void)
{
    USART_Handle.pUSARTx = USART1;

    USART_Handle.USART_Config.USART_Baud = USART_STD_BAUD_1200;
    USART_Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    USART_Handle.USART_Config.USART_Mode = USART_MODE_TXRX;
    USART_Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    USART_Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    USART_Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;

    USART_Init(&USART_Handle);
}

void USART1_GPIOInit(void)
{
    GPIO_Handle_t USART1_GPIO;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    USART1_GPIO.pGPIOx = GPIOA;

    USART1_GPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    USART1_GPIO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    USART1_GPIO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    USART1_GPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    USART1_GPIO.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

    // PA9 = TX
    USART1_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&USART1_GPIO);

    // PA10 = RX
    USART1_GPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(&USART1_GPIO);
}

/*
Initialized and configured GPIO Ports for Keypad

Rows    -- PortA - Pin 5-8
Columns -- PortA - Pin 1-4
LED     -- PortD - Pin 12
*/

void GPIO_KeypadInit(void)
{
    /* =========================
       LED : PD12
       ========================= */

    GPIO_Handle_t PD12;

    PD12.pGPIOx = GPIOD;
    PD12.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    PD12.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    PD12.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PD12.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PD12.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    /* =========================
       ROWS : PA5 - PA8
       ========================= */

    GPIO_Handle_t PA5;

    PA5.pGPIOx = GPIOA;
    PA5.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    PA5.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    PA5.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA5.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA5.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_Handle_t PA6;

    PA6.pGPIOx = GPIOA;
    PA6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    PA6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    PA6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_Handle_t PA7;

    PA7.pGPIOx = GPIOA;
    PA7.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    PA7.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    PA7.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_Handle_t PA8;

    PA8.pGPIOx = GPIOA;
    PA8.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    PA8.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    PA8.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    /* =========================
       COLUMNS : PA1 - PA4
       ========================= */

    GPIO_Handle_t PA1;

    PA1.pGPIOx = GPIOA;
    PA1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    PA1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    PA1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


    GPIO_Handle_t PA2;

    PA2.pGPIOx = GPIOA;
    PA2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    PA2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    PA2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


    GPIO_Handle_t PA3;

    PA3.pGPIOx = GPIOA;
    PA3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    PA3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    PA3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


    GPIO_Handle_t PA4;

    PA4.pGPIOx = GPIOA;
    PA4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
    PA4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    PA4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    PA4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    PA4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


    /* =========================
       Enable GPIO clocks
       ========================= */

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOD, ENABLE);


    /* =========================
       Initialize GPIO pins
       ========================= */

    GPIO_Init(&PD12);

    GPIO_Init(&PA5);
    GPIO_Init(&PA6);
    GPIO_Init(&PA7);
    GPIO_Init(&PA8);

    GPIO_Init(&PA1);
    GPIO_Init(&PA2);
    GPIO_Init(&PA3);
    GPIO_Init(&PA4);
}


uint8_t Keypad_GetKey(void)
{
    uint8_t key = 0;


    /* =====================================================
       ROW 0 -> PA5 LOW
       ===================================================== */

    /* All rows HIGH */
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_8, GPIO_PIN_SET);

    /* Row 0 LOW */
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET);

    /* Column 0 -> PA1 */
    if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1)))
    {
        key = '1';
      //  delay(20);
    }

    /* Column 1 -> PA2 */
    else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2)))
    {
        key = '2';
    }

    /* Column 2 -> PA3 */
    else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3)))
    {
        key = '3';
    }

    /* Column 3 -> PA4 */
    else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4)))
    {
        key = 'A';
    }


    /* =====================================================
       ROW 1 -> PA6 LOW
       ===================================================== */

    if(key == 0)
    {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_RESET);

        /* Column 0 */
        if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1)))
        {
            key = '4';
        }

        /* Column 1 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2)))
        {
            key = '5';
        }

        /* Column 2 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3)))
        {
            key = '6';
        }

        /* Column 3 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4)))
        {
            key = 'B';
        }
    }


    /* =====================================================
       ROW 2 -> PA7 LOW
       ===================================================== */

    if(key == 0)
    {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_SET);
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_RESET);

        /* Column 0 */
        if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1)))
        {
            key = '7';
        }

        /* Column 1 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2)))
        {
            key = '8';
        }

        /* Column 2 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3)))
        {
            key = '9';
        }

        /* Column 3 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4)))
        {
            key = 'C';
        }
    }


    /* =====================================================
       ROW 3 -> PA8 LOW
       ===================================================== */

    if(key == 0)
    {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_SET);
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_8, GPIO_PIN_RESET);

        /* Column 0 */
        if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_1)))
        {
            key = '*';
        }

        /* Column 1 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_2)))
        {
            key = '0';
        }

        /* Column 2 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_3)))
        {
            key = '#';
        }

        /* Column 3 */
        else if(!(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4)))
        {
            key = 'D';
        }
    }


    /* Return all rows HIGH */
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_6, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_7, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_8, GPIO_PIN_SET);


    return key;
}

uint8_t TxRx_SendByte(uint8_t data)
{
	txData = data;
	return USART_SendDataIT(&USART_Handle, &txData, 1);
}

void USART1_IRQHandler(void)
{
    USART_IRQHandling(&USART_Handle);
}




/* =========================================================
 * LCD GPIO INITIALIZATION
 * ========================================================= */

void lcd_port_initialize(void)
{
    GPIO_Handle_t LCD_Data;
    GPIO_Handle_t LCD_Control;

    /* Enable GPIO clocks */
    GPIO_PeriClockControl(GPIOD, ENABLE);
    GPIO_PeriClockControl(GPIOC, ENABLE);


    /* =====================================================
     * LCD DATA PINS : PD0 - PD7
     * ===================================================== */

    LCD_Data.pGPIOx = GPIOD;

    LCD_Data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    LCD_Data.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    LCD_Data.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    LCD_Data.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&LCD_Data);

    LCD_Data.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&LCD_Data);


    /* =====================================================
     * LCD CONTROL PINS : PC0, PC1, PC2
     *
     * PC0 -> RS
     * PC1 -> RW
     * PC2 -> EN
     * ===================================================== */

    LCD_Control.pGPIOx = GPIOC;

    LCD_Control.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    LCD_Control.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    LCD_Control.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    LCD_Control.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    /* PC0 -> RS */
    LCD_Control.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIO_Init(&LCD_Control);

    /* PC1 -> RW */
    LCD_Control.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    GPIO_Init(&LCD_Control);

    /* PC2 -> EN */
    LCD_Control.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&LCD_Control);


    /* Initial state */
    GPIO_WriteToOutputPin(GPIOC, RS, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOC, RW, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOC, EN, GPIO_PIN_RESET);
}

#if 0
uint8_t Keypad_GetKeyRaw(void)
{
    uint8_t key;

    key = Keypad_GetKey();

    if (key != 0)
    {
        /* Debounce */
        delay(20);

        /* Confirm the key is still pressed */
        if (Keypad_GetKey() == key)
        {
            /* Wait for release */
            while (Keypad_GetKey() != 0)
            {
                /* Key still pressed */
            }

            /* Release debounce */
            delay(20);

            return key;
        }
    }

    return 0;
}

#endif

/* =========================================================
 * LCD INITIALIZATION
 * ========================================================= */

void lcd_Initizalize(void)
{
    /*
     */

    delay(20);

    /* 8-bit initialization */
    LCD_command(0x30);
    delay(10);

    /* 8-bit, 2-line, 5x8 font */
    LCD_command(0x38);
    delay(10);

    /* Entry mode:
     * cursor moves right
     */
    LCD_command(0x06);
    delay(10);

    /* Clear display */
    LCD_command(0x01);
    delay(10);

    /* Return cursor home */
    LCD_command(0x02);
    delay(10);

    /* Display ON
     * Cursor ON
     * Cursor blinking ON
     */
    LCD_command(0x0F);
    delay(10);
}


/* =========================================================
 * LCD SEND COMMAND
 * ========================================================= */

void LCD_command(unsigned char command)
{
    /*
     * RS = 0 -> command
     * RW = 0 -> write
     */

    GPIO_WriteToOutputPin(GPIOC, RS, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOC, RW, GPIO_PIN_RESET);


    /* Put command on PD0 - PD7 */

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, (command >> 0) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, (command >> 1) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, (command >> 2) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, (command >> 3) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_4, (command >> 4) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_5, (command >> 5) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_6, (command >> 6) & 0x01);

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_7, (command >> 7) & 0x01);


    /* Enable pulse */
    GPIO_WriteToOutputPin(GPIOC, EN, GPIO_PIN_SET);
    delay(1);

    GPIO_WriteToOutputPin(GPIOC, EN, GPIO_PIN_RESET);
    delay(2);
}


/* =========================================================
 * LCD SEND DATA / CHARACTER
 * ========================================================= */

void LCD_data(char data)
{
    /*
     * RS = 1 -> data
     * RW = 0 -> write
     */

    GPIO_WriteToOutputPin(GPIOC, RS, GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOC, RW, GPIO_PIN_RESET);


    /* Put character on PD0 - PD7 */

    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, (data >> 0) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, (data >> 1) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, (data >> 2) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3,(data >> 3) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_4,(data >> 4) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_5,(data >> 5) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_6,(data >> 6) & 0x01);
    GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_7,(data >> 7) & 0x01);


    /* Enable pulse */

    GPIO_WriteToOutputPin(GPIOC, EN, GPIO_PIN_SET);
    delay(1);

    GPIO_WriteToOutputPin(GPIOC, EN, GPIO_PIN_RESET);
    delay(2);
}

/*  Start USART1 Receive  */
void TxRx_StartReceive(void)
{
	USART_ReceiveDataIT(&USART_Handle, &rxData, 1);
}

/* Return received byte */
uint8_t TxRx_GetReceivedByte(void)
{
	rxComplete = 0;
	return rxData;
}

uint8_t TxRx_DataAvailable(void)
{
	return rxComplete;
}

/* USART Application Callback */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t event)
{
    if(event == USART_EVENT_TX_CMPLT)
    {
        /* TX completed */
        GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_12, GPIO_PIN_SET);
    }

    else if(event == USART_EVENT_RX_CMPLT)
    {
        /* RX completed */
        rxComplete = 1;
    }
}


