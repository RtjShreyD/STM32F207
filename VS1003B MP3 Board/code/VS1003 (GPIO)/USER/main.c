/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The VS1003(record) application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2011-2-27
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "vs1003.h"

void delay_ms(u32 ms)
{
	while(ms--);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  VS1003_Init();
  VS1003_Reset();
  VS1003_SoftReset();

  
  	/*GPIOÊä³ö3.3V*/
	VS1003_WriteReg(SPI_WRAMADDR,0xc017);
	VS1003_WriteReg(SPI_WRAM,0x000f);

  while(1)
  {

	VS1003_WriteReg(SPI_WRAMADDR,0xc019);
	VS1003_WriteReg(SPI_WRAM,0x000f);
	delay_ms(0x1fffff);
		 /*GPIOÊä³ö3.3V*/

	VS1003_WriteReg(SPI_WRAMADDR,0xc019);
	VS1003_WriteReg(SPI_WRAM,0x0000);	
	delay_ms(0x1fffff); 	 

  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

