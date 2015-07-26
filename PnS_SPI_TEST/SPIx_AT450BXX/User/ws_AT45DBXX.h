/*********************************************************************************************************
*
* File                : ws_AT45DBXX.h
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

#ifndef _AT45DBXX_H
#define _AT45DBXX_H

#define SST25VF040 2
#define W25X40BV   1

#define BUF1_WRITE 0x84
#define BUF2_WRITE 0x87
#define BUF1_READ 0xD4
#define BUF2_READ 0xD6
#define BBUF1_TO_MM_PAGE_PROG_WITH_ERASE 0x83
#define BBUF2_TO_MM_PAGE_PROG_WITH_ERASE 0x86
#define MM_PAGE_TO_B1_XFER 0x53
#define MM_PAGE_TO_B2_XFER 0x55
#define PAGE_ERASE 0x81   // 512/528 bytes per page
#define SECTOR_ERASE 0x7C // 128k bytes per sector

//SST25VF040 SPI FLASH & WINBOND W25X040BV FLASH Same Address
#define READ_STATE_REGISTER 0x05 //sst25vf040  //0xD7
#define Read_ID 0xAB//90
#define Read_Data 0x03
#define PAGE_WIRTE 0x02 //256 Byte Continu
#define WRITE_ENABLE 0x06
#define EWSR 0x50 //Enable Write status Register
#define WRSR 0x01 //Write Status Register
#define DUMMY 0xA5
#define START_ADDRESS 0x00
#define END_ADDRESS 0x7FFFF

//
#define COPY_START 0x01
#define DATA_All_VERIFY 0x02


//WINBOND W25X040BV FLASH

//
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




#define SPI_CS1_Enable 	GPIO_ResetBits(Open207Z_SPI1_CS_GPIO_PORT,Open207Z_SPI1_CS_PIN);
#define SPI_CS1_Disable 	GPIO_SetBits(Open207Z_SPI1_CS_GPIO_PORT,Open207Z_SPI1_CS_PIN);


#define SPI_CS2_Enable 	GPIO_ResetBits(Open207Z_SPI2_CS_GPIO_PORT,Open207Z_SPI2_CS_PIN);
#define SPI_CS2_Disable 	GPIO_SetBits(Open207Z_SPI2_CS_GPIO_PORT,Open207Z_SPI2_CS_PIN);

void SPIx_Init(u8 SPI_NUMBER);
//static void SPIx_BusyCheck(u8 SPI_Number);
static void SPIx_BusyCheck(u8 SPI_Number);

void Write_Status_Register(u8 SPI_Number);


void SPIx_Read_ID(u8 SPI_CH, u8 *IData);


void Read_Status_Register(u8 SPIx);

void write_buffer(u8 SPI_CH, u32 BufferOffset,u8 Data);

u8 read_buffer(u8 SPI_CH,u32 BufferOffset);

void ContinueRead(u32 StartAddress, u32 EndAdress, u8 *Flash);

void ChipEraser(u8 SPI_CH);

void Write_Enable (u8 SPI_CH);

void Compair_Match(u32 StartAddress, u32 EndAddress);



#include "ws_spi.h"

#endif /*_AT45DBXX_H*/

