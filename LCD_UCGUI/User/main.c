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
#include "config.h"
#include "JOYState.h"
#include "LCD.h"
#include "GUI.h"
#include "TouchPanel.h"
#include "GUIDEMO.h"




char Touch_Screen_Start=0;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
 GPIO_InitTypeDef t_Gpio_init;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
        system_stm32f2xx.c file
     */
    SystemInit();
  	SystemCoreClockUpdate();	
	USART_Configuration();
	USART_NVIC_Config();
	JOYState_LED_GPIO_Init();
	GUI_Init();
    TP_Init();
	//Systickconfig
	SysTick_Config(SystemCoreClock/1000);//120000

   	Touch_Screen_Start = 1;
//   _ExecCalibration();	  /* Calibrate touch panel */
//   _cbDialog();
   	for(;;)
   	{
   		//GUIDEMO_main();
		GUIDEMO_Graph();
    }
	
	/*LCD_Initializtion();
	LCD_Clear(White);*/



	
//	printf("\r\nBoot Success\r\n");

	while (1)
	{
//		LCD_Clear(White);
		GUI_Text(64,104,"P&S Technology",Black,White);
		GUI_Text(64,120,"RnD / H/W Team",Black,White);
		GUI_Text(64,136,"Assistant Research Engineer",Black,White);
		GUI_Text(64,152,"S.Jung",Black,White);





	
		Led_Toggle(Read_JOYState());

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
