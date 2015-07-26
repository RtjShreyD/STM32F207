/*********************************************************************************************************
*
* File                : ws_AT45DBXX.c
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
#include "usart.h"
#include "ws_AT45DBXX.h"
#include <string.h>
#include <stdio.h>

void SPIx_Init(u8 SPI_NUMBER)
{
	switch (SPI_NUMBER)
	{
		case 1:
			SPI1_Configuration();
			SPI_CS1_Disable;
			printf("SPI 1 Channel Init Complete\r\n");
			break;
												   
		case 2:
			SPI2_Configuration();
			SPI_CS2_Disable;
			printf("SPI 2 Channel Init Complete\r\n");
			break;
		default :
			printf("SPI Channel Select Error\r\n");
			break;
	}



	printf("SPI is ready!\r\n");
  SPI_CS1_Disable;  	
  SPI_CS2_Disable;
}

void Read_Status_Register(u8 SPIx)
{
	u8 temp=0;
	switch (SPIx)
	{
	
	case 1:
		SPIx_BusyCheck(1);
		SPI_CS1_Enable;
		SPI1_Send_byte(READ_STATE_REGISTER);
		temp = SPI1_Receive_byte();
		printf("SPI1 Status Register : 0x%x \r\n",temp);
		SPI_CS1_Disable;		
	break;

	case 2:
		SPIx_BusyCheck(2);
		SPI_CS2_Enable;
		SPI2_Send_byte(READ_STATE_REGISTER);
		temp = SPI2_Receive_byte();
		printf("SPI2 Status Register : 0x%x \r\n",temp);
		SPI_CS2_Enable;		
	break;

	default:			
	break;
	
	
		}
}


static void SPIx_BusyCheck(u8 SPI_Number)
{
	u8 Busy_Check,Busy=1;
	switch(SPI_Number)
	{
		case 1:
		SPI_CS1_Enable;
		SPI1_Send_byte(READ_STATE_REGISTER);
		do {
			Busy_Check = SPI1_Receive_byte();
			if( (Busy_Check & 0x01) == 0x01)
				{Busy = 1;}
			else {Busy = 0;}
			}
		while(Busy);
		SPI_CS1_Disable;
		break;
		
		case 2:
		SPI_CS2_Enable;
		SPI2_Send_byte(READ_STATE_REGISTER);

		do {
			Busy_Check = SPI2_Receive_byte();
			if( (Busy_Check & 0x01) == 0x01)
				{Busy = 1;}
			else {Busy = 0;}
			}
		while(Busy);

		SPI_CS2_Disable;
		break;
		
		default:
		break;
	}			
		
}

void SPIx_Read_ID(u8 SPI_CH, u8 *IData)
{
	u8 i=0;
	switch (SPI_CH)
	{
	case 1:
	SPIx_BusyCheck(1);
	SPI_CS1_Enable;
	SPI1_Send_byte(0x90); //
	SPI1_Send_byte(0x00); //dummy
	SPI1_Send_byte(0x00); //dummy
	SPI1_Send_byte(0x00);
  	for(i=0;i<2;i++)
  	{
  		IData[i] = SPI1_Receive_byte();
  	}
  	SPI_CS1_Disable;
	break;

	case 2:				
	SPIx_BusyCheck(2);
	SPI_CS2_Enable;
	SPI2_Send_byte(Read_ID); //
	SPI2_Send_byte(0x00); //dummy
	SPI2_Send_byte(0x00); //dummy
	SPI2_Send_byte(0x00);
  	for(i=0;i<2;i++)
  	{
  		IData[i] = SPI2_Receive_byte();
  	}
  	SPI_CS2_Disable;
	break;

	default:
		printf("SPI Ch Select Error\r\n");
	break;
	}
	
}

void Write_Status_Register(u8 SPI_Number)
{
	u8 tmp=0;
	switch(SPI_Number)
	{
		case 1:
		// Read Status Register
		SPIx_BusyCheck(1);
		SPI_CS1_Enable;
		SPI1_Send_byte(READ_STATE_REGISTER);
		tmp = SPI1_Receive_byte();
		SPI_CS1_Disable;

		// Status Register Write Enable
		//SPIx_BusyCheck(1);
		SPI_CS1_Enable;
		SPI1_Send_byte(EWSR);
		SPI_CS1_Disable;

		// Write Status Register Wirte Protect Disable
		SPI_CS1_Enable;
		SPI1_Send_byte(WRSR);
		SPI1_Send_byte(tmp&0xC3); //BP3~BP0 Write Protect bit Clear
		SPI_CS1_Disable;
		
		break;

		case 2:
			// Read Status Register
			SPIx_BusyCheck(2);
			SPI_CS2_Enable;
			SPI2_Send_byte(READ_STATE_REGISTER);
			tmp = SPI2_Receive_byte();
			SPI_CS2_Disable;
			
			// Status Register Write Enable
			//SPIx_BusyCheck(1);
			SPI_CS2_Enable;
			SPI2_Send_byte(EWSR);
			SPI_CS2_Disable;
			
			// Write Status Register Wirte Protect Disable
			SPI_CS2_Enable;
			SPI2_Send_byte(WRSR);
			SPI2_Send_byte(tmp&0xC3); //BP3~BP0 Write Protect bit Clear
			SPI_CS2_Disable;
		break;

		default:
			
		break;
	}
}


void write_buffer(u8 SPI_CH, u32 BufferOffset,u8 Data)
{			

	switch(SPI_CH)
	{
	case 1:
	SPIx_BusyCheck(1);
	SPI_CS1_Enable;
	SPI1_Send_byte(0x02);
	SPI1_Send_byte((BufferOffset & 0xFF0000)>>16);
	SPI1_Send_byte((BufferOffset & 0xFF00)>>8);
	SPI1_Send_byte(BufferOffset & 0xFF);  
	SPI1_Send_byte(Data);
	SPI_CS1_Disable;
	break;

	case 2:
	SPIx_BusyCheck(2);
	SPI_CS2_Enable;
	SPI2_Send_byte(0x02);			
	SPI2_Send_byte((BufferOffset & 0xFF0000)>>16);
	SPI2_Send_byte((BufferOffset & 0xFF00)>>8);
	SPI2_Send_byte(BufferOffset & 0xFF);  
	SPI2_Send_byte(Data & 0xFF);
	SPI_CS2_Disable;
	break;

	default:
	break;
	}
	
}



u8 read_buffer(u8 SPI_CH,u32 BufferOffset)
{		
	u8 temp=0;

	switch(SPI_CH)
	{
	case 1:
	SPIx_BusyCheck(1);
	SPI_CS1_Enable;
	SPI1_Send_byte(Read_Data);
	SPI1_Send_byte((BufferOffset & 0xFF0000)>>16);
	SPI1_Send_byte((BufferOffset & 0xFF00)>>8);
	SPI1_Send_byte(BufferOffset & 0xFF);  
	temp=SPI1_Receive_byte();
	SPI_CS1_Disable;
	break;		

	case 2:
	SPIx_BusyCheck(2);
	SPI_CS2_Enable;
 	SPI2_Send_byte(Read_Data);
	SPI2_Send_byte((BufferOffset & 0xFF0000)>>16);
	SPI2_Send_byte((BufferOffset & 0xFF00)>>8);
	SPI2_Send_byte(BufferOffset & 0xFF);  
	temp=SPI2_Receive_byte();
	SPI_CS2_Disable;
	break;

	default:
	break;
	
	}
	return temp;		
}

void ContinueRead(u32 StartAddress, u32 EndAdress, u8 *Flash)
{
	volatile u32 Counttemp=0 , i=0;
	Counttemp =  EndAdress-StartAddress;
	SPI_CS1_Enable;
	SPI1_Send_byte(0x0b);
	SPI1_Send_byte((u8)StartAddress>>16);
	SPI1_Send_byte((u8)StartAddress>>8);
	SPI1_Send_byte((u8)StartAddress);
	SPI1_Send_byte(0xFF); //Dummy Data

	for (i=0;i<Counttemp;i++)
	{
		*Flash = SPI1_Receive_byte();

		if (i<256)
		{	printf("Address : [%3d]::[%3d]\r\n", i,*Flash);}
	}

	
	
	SPI_CS1_Disable;
	

}

void ChipEraser(u8 SPI_CH)
{
	if (SPI_CH == 1)
	{
		SPI_CS1_Enable;
		SPI1_Send_byte(WRITE_ENABLE);
		SPI_CS1_Disable;
		
		SPI_CS1_Enable;
		SPI1_Send_byte(0x60);
		SPI_CS1_Disable;
	}
	else if (SPI_CH == 2)
	{

		SPI_CS2_Enable;
		SPI2_Send_byte(WRITE_ENABLE);
		SPI_CS2_Disable;
		
		SPI_CS2_Enable;
		SPI2_Send_byte(0x60);
		SPI_CS2_Disable;

	}
	else{}
	
}

void Write_Enable (u8 SPI_CH)
{
	if (SPI_CH == 1)
	{
	SPIx_BusyCheck(1);
	SPI_CS1_Disable;
	SPI_CS1_Enable;
	SPI1_Send_byte(0x06);
	SPI_CS1_Disable;	
	}
	
	else if (SPI_CH==2)
	{
	SPIx_BusyCheck(2);
	SPI_CS2_Disable;
	SPI_CS2_Enable;
	SPI2_Send_byte(0x06);
	SPI_CS2_Disable;
	}

	else{}

}

void Compair_Match(u32 StartAddress, u32 EndAddress)
{
	u8 DATA[2];
	u32 Address, MaxAddress,StartAdd;
	u32 MissMatch_CNT=0;

	StartAdd = StartAddress;

	
	if (EndAddress >=0x80000 )
	{MaxAddress = EndAddress - 1;}

	else {MaxAddress=EndAddress;}

	
	for (Address = StartAdd ; Address <= MaxAddress; Address++)
	{
			 DATA[0] = read_buffer(1,Address);
			 DATA[1] = read_buffer(2,Address);
			 printf(".");
			if( memcmp(&DATA[0],&DATA[1],1) != 0)
			{
				printf("[%6d]Address Data fail!!\r\n",Address);
				printf("[%3d]::[%3d]\r\n",DATA[0],DATA[1]);
				MissMatch_CNT++;
			}							   
	}

		
		printf("\r\nMatch Complete\r\n");
		printf("\r\nMiss Match Counter [%6d]\r\n",MissMatch_CNT);


}
			 
