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
#include "usart.h"
#include "LCD/LCD.h"
#include "camera/dcmi_OV7670.h"

/** @addtogroup STM32F2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup IOToggle
  * @{
  */ 

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	OV7670_IDTypeDef OV7670ID;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */

	USART_Configuration();
	//USART_NVIC_Config();

	LCD_Initializtion();
	LCD_Clear(Red);
	//GUI_Text(50,70,"Camera Init..",White,Red);

	printf("\r\n\r\nWelcome to WaveShare STM32F2 series MCU Board Open207Z\r\n");
	printf("OV7670 Init..\r\n");
	if(DCMI_OV7670_Init()==0){
		printf("Camera Have Init..\r\n");
		//GUI_Text(50,90,"Camera Have Init..",White,Red);
		}
	else {
		printf("OV7670 Init fails!!\r\n");
		//GUI_Text(50,90,"OV7670 Init fails!!",White,Red);
		}

		DCMI_OV7670_ReadID(&OV7670ID);
	if(DCMI_OV7670_ReadID(&OV7670ID)==0)
	{	   
		if(OV7670ID.Manufacturer_ID1==0x7f || OV7670ID.Manufacturer_ID2==0xa2 ||OV7670ID.Version==0x73 ||OV7670ID.PID==0x76)
			printf("OV7670 ID:0x%x 0x%x 0x%x 0x%x\r\n",OV7670ID.Manufacturer_ID1, OV7670ID.Manufacturer_ID2, OV7670ID.PID, OV7670ID.Version);
		else
			printf("OV7670 ID is Error!\r\n");	  
	}
			
	LCD_WriteReg(0x0011,0x6078);
	LCD_SetCursor(0,0);
	LCD_REG = 0x0022;

	/* Start Image capture and Display on the LCD *****************************/
    /* Enable DMA transfer */
    DMA_Cmd(DMA2_Stream1, ENABLE);

    /* Enable DCMI interface */
    DCMI_Cmd(ENABLE); 

    /* Start Image capture */ 
    DCMI_CaptureCmd(ENABLE);
	
	if(DCMI_SingleRandomWrite(0x71, 0x80)!=0); //color test	on
	delay_ms(0x5fff);
	if(DCMI_SingleRandomWrite(0x71, 0x00)!=0); //color test off

	while (1)
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
