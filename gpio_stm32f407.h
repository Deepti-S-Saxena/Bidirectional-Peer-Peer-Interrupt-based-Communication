/* gpio_stm32f407.h */


#ifndef GPIO_STM32F407_H_
#define GPIO_STM32F407_H_


#include "stm32f407.h"

typedef struct
{
uint8_t GPIO_PinNumber;
uint8_t GPIO_PinMode;
uint8_t GPIO_PinSpeed;
uint8_t GPIO_PinPuPdControl;
uint8_t GPIO_PinOPType;
uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;


/* The handle structure for a GPIO pin */

typedef struct
{
GPIO_RegDef_t *pGPIOx;   /*This holds the base address of the GPIO part to which the pin belongs*/
GPIO_PinConfig_t GPIO_PinConfig; /* This holds GPIO pin configuration settings */

}GPIO_Handle_t;

/* GPIO pin possible numbers */

#define GPIO_PIN_NO_0 			0
#define GPIO_PIN_NO_1 			1
#define GPIO_PIN_NO_2 			2
#define GPIO_PIN_NO_3 			3
#define GPIO_PIN_NO_4 			4
#define GPIO_PIN_NO_5 			5
#define GPIO_PIN_NO_6 			6
#define GPIO_PIN_NO_7 			7
#define GPIO_PIN_NO_8 			8
#define GPIO_PIN_NO_9 			9
#define GPIO_PIN_NO_10 			10
#define GPIO_PIN_NO_11 			11
#define GPIO_PIN_NO_12 			12
#define GPIO_PIN_NO_13 			13
#define GPIO_PIN_NO_14 			14
#define GPIO_PIN_NO_15 			15

/* GPIO pin possible modes */

#define GPIO_MODE_IN 			0
#define GPIO_MODE_OUT 			1
#define GPIO_MODE_ALTFN 		2
#define GPIO_MODE_ANALOG 		3
#define GPIO_MODE_IT_FT 		4
#define GPIO_MODE_IT_RT 		5
#define GPIO_MODE_IT_RFT 		6


/* GPIO pin possible output types */
#define GPIO_OP_TYPE_PP 		0
#define GPIO_OP_TYPE_OD 		1


/* GPIO pin possible output speeds */
#define GPIO_SPEED_LOW 			0
#define GPIO_SPEED_MEDIUM 		1
#define GPIO_SPEED_FAST 		2
#define GPIO_SPEED_HIGH 		3


/* GPIO pin possible PULL-UP OR PULL-DOWN states */
#define GPIO_NO_PUPD 			0
#define GPIO_PIN_PU 			1
#define GPIO_PIN_PD 			2

#define GPIO_BASEADDR_TO_CODE(x)  \
    ((x == GPIOA) ? 0 :           \
     (x == GPIOB) ? 1 :           \
     (x == GPIOC) ? 2 :           \
     (x == GPIOD) ? 3 :           \
     (x == GPIOE) ? 4 :           \
     (x == GPIOF) ? 5 :           \
     (x == GPIOG) ? 6 :           \
     (x == GPIOH) ? 7 : 0)

/*********************************************** APIs *******************************************************/

/* Peripheral Clock setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Init and DeInit */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

/* Read and Write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);

#endif /* GPIO_STM32F407_H_ */
