/*********************************************************************************************************
*
* File                : ws_spi.h
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

#ifndef __SPI_H
#define __SPI_H

void SPI2_Configuration(void);
void SPI1_Configuration(void);

void SPI2_Send_byte(u16 data);
u16 SPI2_Receive_byte(void);
void SPI1_Send_byte(u16 data);
u16 SPI1_Receive_byte(void);


#endif /*__SPI_H*/
