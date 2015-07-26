/*********************************************************************************************************
*
* File                : sw_spi.c
* Hardware Environment: 
* Build Environment   : RealView MDK-ARM  Version: 4.20
* Version             : V1.0
* By                  : 
*
*                                  (c) Copyright 2005-2011, WaveShare
*                                       http://www.waveshare.net
*                                          All Rights Reserved
*
*********************************************************************************************************/

#include "stm32f2xx.h"
#include "config.h"
#include "ws_spi.h"
#include "ws_AT45DBXX.h"

//############### SPI1 Define ######################
#define Open207Z_SPI1							SPI1

#define Open207Z_SPI1_CLK						RCC_APB2Periph_SPI1
#define Open207Z_SPI1_IRQn						SPI1_IRQn
#define Open207Z_SPI1_IRQHANDLER				SPI1_IRQHandler

#define Open207Z_SPI1_SCK_PIN					GPIO_Pin_5
#define Open207Z_SPI1_SCK_GPIO_PORT 			GPIOA
#define Open207Z_SPI1_SCK_GPIO_CLK				RCC_AHB1Periph_GPIOA
#define Open207Z_SPI1_SCK_SOURCE				GPIO_PinSource5
#define Open207Z_SPI1_SCK_AF					GPIO_AF_SPI1

#define Open207Z_SPI1_MISO_PIN					GPIO_Pin_6
#define Open207Z_SPI1_MISO_GPIO_PORT			GPIOA
#define Open207Z_SPI1_MISO_GPIO_CLK 			RCC_AHB1Periph_GPIOA
#define Open207Z_SPI1_MISO_SOURCE				GPIO_PinSource6
#define Open207Z_SPI1_MISO_AF					GPIO_AF_SPI1

#define Open207Z_SPI1_MOSI_PIN					GPIO_Pin_7
#define Open207Z_SPI1_MOSI_GPIO_PORT			GPIOA
#define Open207Z_SPI1_MOSI_GPIO_CLK 			RCC_AHB1Periph_GPIOA
#define Open207Z_SPI1_MOSI_SOURCE				GPIO_PinSource7
#define Open207Z_SPI1_MOSI_AF					GPIO_AF_SPI1

//############### SPI2 Define ######################
#define Open207Z_SPI2                           SPI2
#define Open207Z_SPI2_CLK                       RCC_APB1Periph_SPI2
#define Open207Z_SPI2_IRQn                      SPI2_IRQn
#define Open207Z_SPI2_IRQHANDLER                SPI2_IRQHandler

#define Open207Z_SPI2_SCK_PIN                   GPIO_Pin_13
#define Open207Z_SPI2_SCK_GPIO_PORT             GPIOB
#define Open207Z_SPI2_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define Open207Z_SPI2_SCK_SOURCE                GPIO_PinSource13
#define Open207Z_SPI2_SCK_AF                    GPIO_AF_SPI2

#define Open207Z_SPI2_MISO_PIN                  GPIO_Pin_14
#define Open207Z_SPI2_MISO_GPIO_PORT            GPIOB
#define Open207Z_SPI2_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define Open207Z_SPI2_MISO_SOURCE               GPIO_PinSource14
#define Open207Z_SPI2_MISO_AF                   GPIO_AF_SPI2

#define Open207Z_SPI2_MOSI_PIN                  GPIO_Pin_15
#define Open207Z_SPI2_MOSI_GPIO_PORT            GPIOB
#define Open207Z_SPI2_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define Open207Z_SPI2_MOSI_SOURCE               GPIO_PinSource15
#define Open207Z_SPI2_MOSI_AF                   GPIO_AF_SPI2


//SPI1 - CS
#define Open207Z_SPI1_CS_PIN                   GPIO_Pin_4
#define Open207Z_SPI1_CS_GPIO_PORT             GPIOA
#define Open207Z_SPI1_CS_GPIO_CLK              RCC_AHB1Periph_GPIOA

//SPI2 - CS
#define Open207Z_SPI2_CS_PIN                   GPIO_Pin_12
#define Open207Z_SPI2_CS_GPIO_PORT             GPIOB
#define Open207Z_SPI2_CS_GPIO_CLK              RCC_AHB1Periph_GPIOB

//SPI3 - CS
#define Open207Z_SPI3_CS_PIN                   GPIO_Pin_4
#define Open207Z_SPI3_CS_GPIO_PORT             GPIOA
#define Open207Z_SPI3_CS_GPIO_CLK              RCC_AHB1Periph_GPIOA





void SPI1_Configuration(void)
{

	SPI_InitTypeDef SPI_InitStruct;	 
	GPIO_InitTypeDef GPIO_InitStructure;

	//CS Pin Setting
	RCC_AHB1PeriphClockCmd(Open207Z_SPI1_CS_GPIO_CLK,ENABLE);

	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI1_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open207Z_SPI1_CS_GPIO_PORT, &GPIO_InitStructure);


	SPI_CS1_Disable;

//SPI Setting	
	RCC_AHB1PeriphClockCmd(Open207Z_SPI1_SCK_GPIO_CLK | Open207Z_SPI1_MISO_GPIO_CLK | Open207Z_SPI1_MOSI_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(Open207Z_SPI1_CLK,ENABLE); //spi1
	
	
	GPIO_PinAFConfig(Open207Z_SPI1_SCK_GPIO_PORT, Open207Z_SPI1_SCK_SOURCE,  Open207Z_SPI1_SCK_AF);
	GPIO_PinAFConfig(Open207Z_SPI1_MISO_GPIO_PORT, Open207Z_SPI1_MISO_SOURCE, Open207Z_SPI1_MISO_AF);
	GPIO_PinAFConfig(Open207Z_SPI1_MOSI_GPIO_PORT, Open207Z_SPI1_MOSI_SOURCE, Open207Z_SPI1_MOSI_AF);
	
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI1_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
	GPIO_Init(Open207Z_SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI1_MISO_PIN;
	GPIO_Init(Open207Z_SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI1_MOSI_PIN;
	GPIO_Init(Open207Z_SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);

	SPI_I2S_DeInit(Open207Z_SPI1);
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft ;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(Open207Z_SPI1, &SPI_InitStruct);

	SPI_Cmd(Open207Z_SPI1, ENABLE);




}



void SPI2_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStruct;	 
	GPIO_InitTypeDef GPIO_InitStructure;


//CS Pin Setting
RCC_AHB1PeriphClockCmd(Open207Z_SPI2_CS_GPIO_CLK,ENABLE);

GPIO_InitStructure.GPIO_Pin = Open207Z_SPI2_CS_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(Open207Z_SPI2_CS_GPIO_PORT, &GPIO_InitStructure);

SPI_CS2_Disable;	


// SPI Setting	
	RCC_AHB1PeriphClockCmd(Open207Z_SPI2_SCK_GPIO_CLK | Open207Z_SPI2_MISO_GPIO_CLK | Open207Z_SPI2_MOSI_GPIO_CLK,ENABLE);
	RCC_APB1PeriphClockCmd(Open207Z_SPI2_CLK,ENABLE); //spi2

	
	GPIO_PinAFConfig(Open207Z_SPI2_SCK_GPIO_PORT, Open207Z_SPI2_SCK_SOURCE,  Open207Z_SPI2_SCK_AF);
	GPIO_PinAFConfig(Open207Z_SPI2_MISO_GPIO_PORT, Open207Z_SPI2_MISO_SOURCE, Open207Z_SPI2_MISO_AF);
	GPIO_PinAFConfig(Open207Z_SPI2_MOSI_GPIO_PORT, Open207Z_SPI2_MOSI_SOURCE, Open207Z_SPI2_MOSI_AF);
	
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI2_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
	GPIO_Init(Open207Z_SPI2_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;//
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI2_MISO_PIN;
	GPIO_Init(Open207Z_SPI2_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = Open207Z_SPI2_MOSI_PIN;
	GPIO_Init(Open207Z_SPI2_MOSI_GPIO_PORT, &GPIO_InitStructure);


	SPI_I2S_DeInit(Open207Z_SPI2);
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(Open207Z_SPI2, &SPI_InitStruct);

	SPI_Cmd(Open207Z_SPI2, ENABLE);






}

void SPI2_Send_byte(u16 data)
{
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open207Z_SPI2,data);

	while(SPI_I2S_GetFlagStatus(Open207Z_SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(Open207Z_SPI2);
}

u16 SPI2_Receive_byte(void)
{
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI2, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open207Z_SPI2,0xFF);
	
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI2, SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(Open207Z_SPI2);
}

void SPI1_Send_byte(u16 data)
{
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI1, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open207Z_SPI1,data);

	while(SPI_I2S_GetFlagStatus(Open207Z_SPI1, SPI_I2S_FLAG_RXNE)==RESET);
	SPI_I2S_ReceiveData(Open207Z_SPI1);
}

u16 SPI1_Receive_byte(void)
{
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI1, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(Open207Z_SPI1,0xFF);
	
	while(SPI_I2S_GetFlagStatus(Open207Z_SPI1, SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(Open207Z_SPI1);
}



