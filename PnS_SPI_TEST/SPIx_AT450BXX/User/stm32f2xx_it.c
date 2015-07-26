/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f2xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f2xx_it.h"
#include "usart.h"
#include "ws_AT45DBXX.h"

u8 ID[4];
extern u8 UART_DATA;

#ifdef OpenUSART1
	#define USARTx_IRQHANDLER   USART1_IRQHandler
#endif
#ifdef OpenUSART2
	#define USARTx_IRQHANDLER   USART2_IRQHandler
#endif
#ifdef OpenUSART3
	#define USARTx_IRQHANDLER   USART3_IRQHandler
#endif
#ifdef OpenUART4
	#define USARTx_IRQHANDLER   UART4_IRQHandler
#endif
#ifdef OpenUART5
	#define USARTx_IRQHANDLER   UART5_IRQHandler
#endif
#ifdef OpenUSART6
	#define USARTx_IRQHANDLER   USART6_IRQHandler
#endif


/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F2xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f2xx.s).                                               */
/******************************************************************************/
void USARTx_IRQHANDLER(void)
{
	u16 Recv_Data=0;
	u8 i=0;
	static u8 ch = 2;
  if(USART_GetITStatus(Open207Z_USARTx, USART_IT_RXNE) != RESET)
  { 
		//printf("\n\rUSART1 Hyperterminal Interrupts Receive a word: %c\n\r",USART_ReceiveData(Open207Z_USARTx));

		Recv_Data = USART_ReceiveData(Open207Z_USARTx);
		
		switch (Recv_Data)
		{
			case 'E':
			case 'e':
				printf("ChipErase....\r\n");
				ChipEraser(2);
			break;

			case 's':
			case 'S':
				Read_Status_Register(ch);

			break;

			case 'w':
			case 'W':
				Write_Status_Register(ch);
				printf("Write Protect Disable : SPI%d\r\n",ch);

			break;

			case 'l':
				for (i=0;i<100;i++)
				{
					printf("[%3d]Address :[%3d]\r\n",i,read_buffer(ch,i));
				}
			break;

			case 'r':
			case 'R':
				SPIx_Read_ID(ch,ID);
				printf("SPI[%d] Flash Rom ID is",ch);
				printf(" 0x%x  0x%x \r\n",ID[0],ID[1]);

			break;

			case 'c':
			case 'C':
				if (ch == 2)
					{
					ch =1;
					printf("SPI CH : [%d]\r\n",ch);
					}
				else
					{
					ch = 2;
					printf("SPI CH : [%d]\r\n",ch);
					}
				break;

			case 'm':
			case 'M':
				UART_DATA = DATA_All_VERIFY;
			break;

			case 'k':

				for (i = 0 ; i<100; i++)
				{
					if (ch == 1)
					{
					Write_Enable(ch);
					}

					else{

					Write_Enable(ch);

					}
					write_buffer(ch,i,i);
					printf("ReadAddress [%3d][%3d]\r\n",i,read_buffer(ch,i));

				}
				Recv_Data = 0;
				break;

			case '-':
				UART_DATA = COPY_START;
			break;

			default:
				if ((Recv_Data >= '0') && ( Recv_Data <= '9'))
				{
					if (ch == 1)
					{
					SPI_CS1_Disable;
					SPI_CS1_Enable;
					SPI1_Send_byte(0x06);
					SPI_CS1_Disable;

					}

					else{
					SPI_CS2_Disable;
					SPI_CS2_Enable;
					SPI2_Send_byte(0x06);
					SPI_CS2_Disable;
					}
					write_buffer(ch,Recv_Data-48,Recv_Data-48);
					printf("ReadAddress [%3d]\r\n",read_buffer(ch,Recv_Data-48));
				}
				else{}
			break;
			
		}
		
		
  }
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
