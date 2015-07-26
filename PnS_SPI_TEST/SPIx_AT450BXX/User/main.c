/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "config.h"
#include "usart.h"
#include "ws_AT45DBXX.h"
#include "System_stm32f2xx.h"
#include <string.h>
#include <stdio.h>

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

void GPIO_Configuration(void);
void MemCopy(void);
void Delay(__IO uint32_t nCount);
u8 bufff[4096];
u8 UART_DATA=0;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
 
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */
	
	u8 ID[4];
	volatile u8 tmp,k;

	


    //SystemInit();
  	//SystemCoreClockUpdate();

	Open207_LEDInit();	
	USART_Configuration();
	USART_NVIC_Config();
	printf("\r\n SPI Rom Copy SPI1 to SPI2\r\n");

	SPIx_Init(1);
	SPIx_Init(2);
	Read_Status_Register(1);
	Read_Status_Register(2);

	


	SPIx_Read_ID(1,ID);
	printf("SPI1 Flash Rom ID is");
	printf(" 0x%x  0x%x \r\n",ID[0],ID[1]);

	SPIx_Read_ID(2,ID);
	printf("SPI2 Flash Rom ID is");
	printf(" 0x%x  0x%x \r\n",ID[0],ID[1]);




/*
	for (i=0 ; i<255; i++)
	{
		 tmp = read_buffer(2,i);
		 printf("intel[%3d] ::",tmp);
		 write_buffer(1,i,tmp);
		 tmp = read_buffer(1,i);
		 printf("[%3d] copy\r\n",tmp);


	}
*/


printf("========Flash Rom Copy========\r\n");
printf("[C]SPI CH Select (Default : 2)\r\n");
printf("[S]Read Status Register\r\n");
printf("[W]Write Protect Disable\r\n");
printf("[R]Read ID\r\n");
printf("[E]Eraser Flash Memory\r\n");
printf("[L]Read Address 0 to 99\r\n");
printf("[-]Copy Start SPI1 to SPI2 \r\n");
printf("[M]Compare Match SPI1 Vs SPI2\r\n");
printf("========Press Key========\r\n");




















	
	while (1)
	{

		GPIO_SetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED2);
		GPIO_SetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED3);
		GPIO_SetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED4);
		Delay(0x5fffff);

		GPIO_ResetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED2);
		GPIO_ResetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED3);
		GPIO_ResetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED4);
		Delay(0x5fffff);

		if (UART_DATA == COPY_START)
		{
			UART_DATA = 0;
			MemCopy();
		}

		else if (UART_DATA == DATA_All_VERIFY)
		{
			UART_DATA = 0;
			Compair_Match(START_ADDRESS,END_ADDRESS);
		}
	
	}

	
}

void MemCopy(void)
{
	volatile u32 i;
	u8 SPI_DATA[2];
	u8 Write_Error = 0;
	printf("Copy Start.......\r\n");
	for (i=START_ADDRESS ; i<END_ADDRESS+1; i++)
	{
		
		GPIO_SetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED4);
		 SPI_DATA[0] = read_buffer(1,i);
	
		 Write_Enable(2);
		 
		 write_buffer(2,i,SPI_DATA[0]);
	
		 SPI_DATA[1] = read_buffer(2,i);
	
		if( memcmp(&SPI_DATA[0],&SPI_DATA[1],1) != 0) // First Matching Miss
		{
			//second Data Copy 
			write_buffer(2,i,SPI_DATA[0]);
			SPI_DATA[1] = read_buffer(2,i);
			
			//Second Data Wirte Error Check
			if( memcmp(&SPI_DATA[0],&SPI_DATA[1],1) != 0) // Second Data Write Matching Miss
			{
				//Stop Write And Display Error
				printf("[%5x]Address Data fail!!\r\n",i);
				printf("[%3d]::[%3d]\r\n",SPI_DATA[0],SPI_DATA[1]);
				printf("SPI Data Copy Stopped \r\n");
				Write_Error = 1;
				GPIO_SetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED1);
				break;
			}
	
			// Second Data OK!
			else
			{
				printf("[%5x]Address Data Verify Error Check and Correct \r\n",i);
			}
		}
	
		SPI_DATA[0] = 0;
		SPI_DATA[1] = 0;
	
		GPIO_ResetBits(Open207Z_LED_GPIO , Open207Z_GPIO_Pin_LED4);
	}

	if (Write_Error != 1)
	{
		printf("Memory Copy Success\r\n");
	}

}


/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {

  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
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

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
