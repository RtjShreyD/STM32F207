#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include "stm32f2xx.h"


/**
 * @brief connected to USART1
 */
/*--------------------USART----------------------------*/
#define OpenUSART1
//#define OpenUSART2
//#define OpenUSART3
//#define OpenUART4
//#define OpenUART5

/*--------------------SPI------------------------------*/
//#define OpenSPI1
#define OpenSPI2
//#define OpenSPI3

/*--------------------I2C------------------------------*/
//#define OpenI2C1
#define OpenI2C2
//#define OpenI2C3

/*--------------------LED-----------------------------*/
#define Open207Z_LED_GPIO_CLK							RCC_AHB1Periph_GPIOF
#define Open207Z_LED_GPIO								GPIOF

#define Open207Z_GPIO_Pin_LED1							GPIO_Pin_6
#define Open207Z_GPIO_Pin_LED2							GPIO_Pin_7
#define Open207Z_GPIO_Pin_LED3							GPIO_Pin_8
#define Open207Z_GPIO_Pin_LED4							GPIO_Pin_9
/*----------------------------------------------------*/

/*--------------------CAN-----------------------------*/
#define OpenCAN1
//#define OpenCAN2
/*----------------------------------------------------*/

#ifdef OpenUSART1  
	#define Open207Z_USARTx                        	USART1
	
	#define Open207Z_USARTx_CLK                    	RCC_APB2Periph_USART1
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_9
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource9
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_USART1
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_10
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource10
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_USART1
	
	#define Open207Z_USARTx_CTS_PIN                 GPIO_Pin_11
	#define Open207Z_USARTx_CTS_GPIO_PORT           GPIOA
	#define Open207Z_USARTx_CTS_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_CTS_SOURCE              GPIO_PinSource11
	#define Open207Z_USARTx_CTS_AF                  GPIO_AF_USART1
	
	#define Open207Z_USARTx_RTS_PIN                 GPIO_Pin_12
	#define Open207Z_USARTx_RTS_GPIO_PORT           GPIOA
	#define Open207Z_USARTx_RTS_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_RTS_SOURCE              GPIO_PinSource12
	#define Open207Z_USARTx_RTS_AF                  GPIO_AF_USART1
	
	#define Open207Z_USARTx_IRQn                   	USART1_IRQn
#endif
#ifdef OpenUSART2
	#define Open207Z_USARTx                        	USART2
	#define Open207Z_USARTx_CLK                    	RCC_APB1Periph_USART2
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_2
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource2
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_USART2
	
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_3
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource3
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_USART2
	
	#define Open207Z_USARTx_CTS_PIN                 GPIO_Pin_0
	#define Open207Z_USARTx_CTS_GPIO_PORT           GPIOA
	#define Open207Z_USARTx_CTS_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_CTS_SOURCE              GPIO_PinSource0
	#define Open207Z_USARTx_CTS_AF                  GPIO_AF_USART2
	
	#define Open207Z_USARTx_RTS_PIN                 GPIO_Pin_1
	#define Open207Z_USARTx_RTS_GPIO_PORT           GPIOA
	#define Open207Z_USARTx_RTS_GPIO_CLK            RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_RTS_SOURCE              GPIO_PinSource1
	#define Open207Z_USARTx_RTS_AF                  GPIO_AF_USART2
	
	#define Open207Z_USARTx_IRQn                    USART2_IRQn
#endif
#ifdef OpenUSART3
	#define Open207Z_USARTx                        	USART3
	#define Open207Z_USARTx_CLK                    	RCC_APB1Periph_USART3
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_10
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOB
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource10
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_USART3
	
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_11
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOB
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource11
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_USART3
	
	#define Open207Z_USARTx_CTS_PIN                 GPIO_Pin_13
	#define Open207Z_USARTx_CTS_GPIO_PORT           GPIOB
	#define Open207Z_USARTx_CTS_GPIO_CLK            RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_CTS_SOURCE              GPIO_PinSource13
	#define Open207Z_USARTx_CTS_AF                  GPIO_AF_USART3
	
	#define Open207Z_USARTx_RTS_PIN                 GPIO_Pin_14
	#define Open207Z_USARTx_RTS_GPIO_PORT           GPIOB
	#define Open207Z_USARTx_RTS_GPIO_CLK            RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_RTS_SOURCE              GPIO_PinSource14
	#define Open207Z_USARTx_RTS_AF                  GPIO_AF_USART3
	
	#define Open207Z_USARTx_IRQn                    USART3_IRQn
#endif
#ifdef OpenUART4
	#define Open207Z_USARTx                        	UART4
	#define Open207Z_USARTx_CLK                    	RCC_APB1Periph_UART4
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_0
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource0
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_UART4
	
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_1
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOA
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource1
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_UART4
	
	#define Open207Z_USARTx_IRQn                    UART4_IRQn
#endif
#ifdef OpenUART5
	#define Open207Z_USARTx                        	UART5
	#define Open207Z_USARTx_CLK                    	RCC_APB1Periph_UART5
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_12
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOC
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOC
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource12
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_UART5
	
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_2
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOD
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOD
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource2
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_UART5
	
	#define Open207Z_USARTx_IRQn                    UART5_IRQn
#endif
#ifdef OpenUSART6/*
	#define Open207Z_USARTx                        	USART6
	#define Open207Z_USARTx_CLK                    	RCC_APB1Periph_USART6
	
	#define Open207Z_USARTx_TX_PIN                 	GPIO_Pin_10
	#define Open207Z_USARTx_TX_GPIO_PORT           	GPIOB
	#define Open207Z_USARTx_TX_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_TX_SOURCE              	GPIO_PinSource10
	#define Open207Z_USARTx_TX_AF                  	GPIO_AF_USART6
	
	
	#define Open207Z_USARTx_RX_PIN                 	GPIO_Pin_11
	#define Open207Z_USARTx_RX_GPIO_PORT           	GPIOB
	#define Open207Z_USARTx_RX_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_RX_SOURCE              	GPIO_PinSource11
	#define Open207Z_USARTx_RX_AF                  	GPIO_AF_USART6
	
	#define Open207Z_USARTx_CTS_PIN                 GPIO_Pin_13
	#define Open207Z_USARTx_CTS_GPIO_PORT           GPIOB
	#define Open207Z_USARTx_CTS_GPIO_CLK            RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_CTS_SOURCE              GPIO_PinSource13
	#define Open207Z_USARTx_CTS_AF                  GPIO_AF_USART6
	
	#define Open207Z_USARTx_RTS_PIN                 GPIO_Pin_14
	#define Open207Z_USARTx_RTS_GPIO_PORT           GPIOB
	#define Open207Z_USARTx_RTS_GPIO_CLK            RCC_AHB1Periph_GPIOB
	#define Open207Z_USARTx_RTS_SOURCE              GPIO_PinSource14
	#define Open207Z_USARTx_RTS_AF                  GPIO_AF_USART6
	
	#define Open207Z_USARTx_IRQn                    USART6_IRQn*/
#endif

/* SPIx Communication boards Interface */
// SPI1 MISO (PA6)	MOSI(PA7)  CLK(PA5)
#ifdef OpenSPI1
	#define Open207Z_SPIx                           SPI1

	#define Open207Z_SPIx_CLK                       RCC_APB2Periph_SPI1
	#define Open207Z_SPIx_IRQn                      SPI1_IRQn
	#define Open207Z_SPIx_IRQHANDLER                SPI1_IRQHandler
	
	#define Open207Z_SPIx_SCK_PIN                   GPIO_Pin_5
	#define Open207Z_SPIx_SCK_GPIO_PORT             GPIOA
	#define Open207Z_SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA
	#define Open207Z_SPIx_SCK_SOURCE                GPIO_PinSource5
	#define Open207Z_SPIx_SCK_AF                    GPIO_AF_SPI1
	
	#define Open207Z_SPIx_MISO_PIN                  GPIO_Pin_6
	#define Open207Z_SPIx_MISO_GPIO_PORT            GPIOA
	#define Open207Z_SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOA
	#define Open207Z_SPIx_MISO_SOURCE               GPIO_PinSource6
	#define Open207Z_SPIx_MISO_AF                   GPIO_AF_SPI1
	
	#define Open207Z_SPIx_MOSI_PIN                  GPIO_Pin_7
	#define Open207Z_SPIx_MOSI_GPIO_PORT            GPIOA
	#define Open207Z_SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
	#define Open207Z_SPIx_MOSI_SOURCE               GPIO_PinSource7
	#define Open207Z_SPIx_MOSI_AF                   GPIO_AF_SPI1
#endif
// SPI2 MISO (PB14)	MOSI(PB15)  CLK(PB13)
#ifdef OpenSPI2
	#define Open207Z_SPIx                           SPI2

	#define Open207Z_SPIx_CLK                       RCC_APB1Periph_SPI2
	#define Open207Z_SPIx_IRQn                      SPI2_IRQn
	#define Open207Z_SPIx_IRQHANDLER                SPI2_IRQHandler
	
	#define Open207Z_SPIx_SCK_PIN                   GPIO_Pin_13
	#define Open207Z_SPIx_SCK_GPIO_PORT             GPIOB
	#define Open207Z_SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
	#define Open207Z_SPIx_SCK_SOURCE                GPIO_PinSource13
	#define Open207Z_SPIx_SCK_AF                    GPIO_AF_SPI2
	
	#define Open207Z_SPIx_MISO_PIN                  GPIO_Pin_14
	#define Open207Z_SPIx_MISO_GPIO_PORT            GPIOB
	#define Open207Z_SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
	#define Open207Z_SPIx_MISO_SOURCE               GPIO_PinSource14
	#define Open207Z_SPIx_MISO_AF                   GPIO_AF_SPI2
	
	#define Open207Z_SPIx_MOSI_PIN                  GPIO_Pin_15
	#define Open207Z_SPIx_MOSI_GPIO_PORT            GPIOB
	#define Open207Z_SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
	#define Open207Z_SPIx_MOSI_SOURCE               GPIO_PinSource15
	#define Open207Z_SPIx_MOSI_AF                   GPIO_AF_SPI2
#endif
#ifdef OpenSPI3
	#define Open207Z_SPIx                           SPI3

	#define Open207Z_SPIx_CLK                       RCC_APB1Periph_SPI3
	#define Open207Z_SPIx_IRQn                      SPI3_IRQn
	#define Open207Z_SPIx_IRQHANDLER                SPI3_IRQHandler
	
	#define Open207Z_SPIx_SCK_PIN                   GPIO_Pin_10
	#define Open207Z_SPIx_SCK_GPIO_PORT             GPIOC
	#define Open207Z_SPIx_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOC
	#define Open207Z_SPIx_SCK_SOURCE                GPIO_PinSource10
	#define Open207Z_SPIx_SCK_AF                    GPIO_AF_SPI3
	
	#define Open207Z_SPIx_MISO_PIN                  GPIO_Pin_11
	#define Open207Z_SPIx_MISO_GPIO_PORT            GPIOC
	#define Open207Z_SPIx_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOC
	#define Open207Z_SPIx_MISO_SOURCE               GPIO_PinSource11
	#define Open207Z_SPIx_MISO_AF                   GPIO_AF_SPI3
	
	#define Open207Z_SPIx_MOSI_PIN                  GPIO_Pin_12
	#define Open207Z_SPIx_MOSI_GPIO_PORT            GPIOC
	#define Open207Z_SPIx_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOC
	#define Open207Z_SPIx_MOSI_SOURCE               GPIO_PinSource12
	#define Open207Z_SPIx_MOSI_AF                   GPIO_AF_SPI3
#endif

/**
 * @brief Definition for COM port1, connected to I2Cx
 */
#ifdef OpenI2C1
	#define Open207Z_I2Cx                        	I2C1
	#define Open207Z_I2Cx_CLK                    	RCC_APB1Periph_I2C1
	
	#define Open207Z_I2Cx_SDA_PIN                 	GPIO_Pin_7
	#define Open207Z_I2Cx_SDA_GPIO_PORT           	GPIOB
	#define Open207Z_I2Cx_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_I2Cx_SDA_SOURCE              	GPIO_PinSource7
	#define Open207Z_I2Cx_SDA_AF                  	GPIO_AF_I2C1
	
	#define Open207Z_I2Cx_SCL_PIN                 	GPIO_Pin_6
	#define Open207Z_I2Cx_SCL_GPIO_PORT           	GPIOB
	#define Open207Z_I2Cx_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_I2Cx_SCL_SOURCE              	GPIO_PinSource6
	#define Open207Z_I2Cx_SCL_AF                  	GPIO_AF_I2C1
#endif
#ifdef OpenI2C2
	#define Open207Z_I2Cx                        	I2C2
	#define Open207Z_I2Cx_CLK                    	RCC_APB1Periph_I2C2
	
	#define Open207Z_I2Cx_SDA_PIN                 	GPIO_Pin_11
	#define Open207Z_I2Cx_SDA_GPIO_PORT           	GPIOB
	#define Open207Z_I2Cx_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_I2Cx_SDA_SOURCE              	GPIO_PinSource11
	#define Open207Z_I2Cx_SDA_AF                  	GPIO_AF_I2C2
	
	#define Open207Z_I2Cx_SCL_PIN                 	GPIO_Pin_10
	#define Open207Z_I2Cx_SCL_GPIO_PORT           	GPIOB
	#define Open207Z_I2Cx_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOB
	#define Open207Z_I2Cx_SCL_SOURCE              	GPIO_PinSource10
	#define Open207Z_I2Cx_SCL_AF                  	GPIO_AF_I2C2
#endif
#ifdef OpenI2C3
	#define Open207Z_I2Cx                        	I2C3
	#define Open207Z_I2Cx_CLK                    	RCC_APB1Periph_I2C3
	
	#define Open207Z_I2Cx_SDA_PIN                 	GPIO_Pin_9
	#define Open207Z_I2Cx_SDA_GPIO_PORT           	GPIOC
	#define Open207Z_I2Cx_SDA_GPIO_CLK            	RCC_AHB1Periph_GPIOC
	#define Open207Z_I2Cx_SDA_SOURCE              	GPIO_PinSource9
	#define Open207Z_I2Cx_SDA_AF                  	GPIO_AF_I2C3
	
	#define Open207Z_I2Cx_SCL_PIN                 	GPIO_Pin_8
	#define Open207Z_I2Cx_SCL_GPIO_PORT           	GPIOA
	#define Open207Z_I2Cx_SCL_GPIO_CLK            	RCC_AHB1Periph_GPIOA
	#define Open207Z_I2Cx_SCL_SOURCE              	GPIO_PinSource8
	#define Open207Z_I2Cx_SCL_AF                  	GPIO_AF_I2C3
#endif

#define I2Cx_SPEED               100000
#define I2Cx_SLAVE_ADDRESS7      0x30

#ifdef  OpenCAN1
  #define Open207Z_CANx                       CAN1
  #define Open207Z_CAN_CLK                    RCC_APB1Periph_CAN1
  #define Open207Z_CAN_RX_PIN                 GPIO_Pin_11
  #define Open207Z_CAN_TX_PIN                 GPIO_Pin_12
  #define Open207Z_CAN_GPIO_PORT              GPIOA
  #define Open207Z_CAN_GPIO_CLK               RCC_AHB1Periph_GPIOA
  #define Open207Z_CAN_AF_PORT                GPIO_AF_CAN1
  #define Open207Z_CAN_RX_SOURCE              GPIO_PinSource11
  #define Open207Z_CAN_TX_SOURCE              GPIO_PinSource12
#endif       
#ifdef OpenCAN2
  #define Open207Z_CANx                       CAN2
  #define Open207Z_CAN_CLK                    RCC_APB1Periph_CAN2
  #define Open207Z_CAN_RX_PIN                 GPIO_Pin_5
  #define Open207Z_CAN_TX_PIN                 GPIO_Pin_13
  #define Open207Z_CAN_GPIO_PORT              GPIOB
  #define Open207Z_CAN_GPIO_CLK               RCC_AHB1Periph_GPIOB
  #define Open207Z_CAN_AF_PORT                GPIO_AF_CAN2
  #define Open207Z_CAN_RX_SOURCE              GPIO_PinSource5
  #define Open207Z_CAN_TX_SOURCE              GPIO_PinSource13    
#endif

void Open207_LEDInit(void);
#endif	  /*_CONFIG_H*/

