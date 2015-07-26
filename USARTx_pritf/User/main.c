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
#include "JOYState.h"
#include "LCD/LCD.h"
#include "TouchPanel/TouchPanel.h"
#include <stdio.h>
#include <math.h>
#define ADC3_DR_ADDRESS    ((uint32_t)0x4001224C)
#define AVCC_mv 3300.0
#define NTC_Resistor 1000 //1Kohm
#define Beta_Constant    3950

__IO uint16_t ADC3ConvertedValue = 0;
__IO uint32_t ADC3ConvertedVoltage = 0;

void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void ADC3_CH7_DMA_Config(void);

void Display_Graph(void);


void Display(void);


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
	//JOYState_LED_GPIO_Init();
	LCD_Initializtion();
	ADC3_CH7_DMA_Config();
	ADC_SoftwareStartConv(ADC3);

		LCD_Clear(Red);
		GUI_Text(132,104,"Open207Z",White,Red);
		//GUI_Text(76,120,"Development Board V1.0",0xFFEF,Red);
		Delay(0xffffff);	
		
		LCD_Clear(Red);
		GUI_Text(76,120,"Development Board V1.0",White,Red);
		Delay(0xffffff);
		LCD_Clear(Black);



	
	printf("\r\nBoot Success\r\n");
	TP_Init();
	TouchPanel_Calibrate();
	Display_Graph();
	while (1)
	{
	
		ADC3ConvertedVoltage = ADC3ConvertedValue *3300/0xFFF;
		Display();
	    getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
		TP_DrawPoint(display.x,display.y);
		//Led_Toggle(Read_JOYState());

	}
}

void Display_Graph(void)
{
	//Graph
	LCD_DrawLine(31,32,31,224,White); // Y line
	LCD_DrawLine(31,224,319,224,White); //under X line
	
	//X Line Time Text (Time)
	//GUI_Text(16,225,"0",White,Black);
	//GUI_Text(106,225,"90",White,Black);//90 sec
	//GUI_Text(196,225,"180",White,Black);//180sec
	//GUI_Text(256,225,"240",White,Black);//240sec
	//GUI_Text(286,225,"270",White,Black);//270sec
	
	//Y Line Time Text(Temp)
	GUI_Text(0,186,"50",White,Black);//50C
	GUI_Text(0,147,"100",Yellow,Black);//100C
	GUI_Text(0,108,"150",Orange,Black);//150C
	GUI_Text(0,70,"200",Orange_Red,Black);//200C
	GUI_Text(0,31,"250",Red,Black);//250C

}

void ADC3_CH7_DMA_Config()
{
ADC_InitTypeDef 	  ADC_InitStructure;
ADC_CommonInitTypeDef ADC_CommonInitStructure;
DMA_InitTypeDef 	  DMA_InitStructure;
GPIO_InitTypeDef	  GPIO_InitStructure;
 
/* Enable ADC3, DMA2 and GPIO clocks ****************************************/
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOF, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

/* DMA2 Stream0 channel2 configuration **************************************/
DMA_InitStructure.DMA_Channel = DMA_Channel_2;	
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
DMA_InitStructure.DMA_BufferSize = 1;
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;		   
DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
DMA_Init(DMA2_Stream0, &DMA_InitStructure);
DMA_Cmd(DMA2_Stream0, ENABLE);

/* Configure ADC3 Channel7 pin as analog input ******************************/
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
GPIO_Init(GPIOF, &GPIO_InitStructure);

/* ADC Common Init **********************************************************/
ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
ADC_CommonInit(&ADC_CommonInitStructure);

/* ADC3 Init ****************************************************************/
ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
ADC_InitStructure.ADC_ScanConvMode = DISABLE;
ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStructure.ADC_NbrOfConversion = 1;
ADC_Init(ADC3, &ADC_InitStructure);

/* ADC3 regular channel7 configuration *************************************/
ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_3Cycles);

/* Enable DMA request after last transfer (Single-ADC mode) */
ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

/* Enable ADC3 DMA */
ADC_DMACmd(ADC3, ENABLE);

/* Enable ADC3 */
ADC_Cmd(ADC3, ENABLE);
}


void Display(void)
{

    /*
      resistance value of NTC:
      r(25)=500 Ohm
      r(t)=r(25)*e^(3300*(1/(t+273)-1/(25+273)))
      etc,
      r(-20)=3.58 KOhm
      r(-3)=1576 KOhm
      r(60)=156 Ohm
      r(100)=54 Ohm
      ...
      if R1=5.6KOhm, then:
      V_in(t)=AVCC*(r(t)/(r(t)+R1))
      etc,
      V_in(-3)=1098 mv
      V_in(100)=47.7 mv
      ...
      
      when V_in is known, 
      r=R1/((AVCC/V_in)-1)
      because of B=3300K, r(25)=500 Ohm:
      t=(1/((ln(r/500)/3300)+(1/(25+273))))-273
    */
unsigned long v=0,mv=0;
float r,t;
unsigned char temp_buf[3];
unsigned int Temp_point=16, X_Pos=32;
static unsigned int Rev_Temp_Point=0, Time=0;


v=(ADC3ConvertedVoltage)/1000;
mv = (ADC3ConvertedVoltage%1000)/100;
printf("Voltage = %d,%d V   \r\n",v,mv);
printf("ADC = %d   \r\n",ADC3ConvertedValue);
r= NTC_Resistor /((AVCC_mv/ADC3ConvertedVoltage)-1.0);
t=1.0/(log(r/1000)/Beta_Constant+(1.0/(25.0+273.0))) - 273;
printf("Temperature = %3f   \r\n",t);

temp_buf[0] = (t/10)+48;
temp_buf[1] = ((char)t%10)+48;


GUI_Text(0,0,&temp_buf[0],White,Black);
GUI_Text(16,0,"C",White,Black);
GUI_Text(0,16,"ADC Temperature Sensing",White,Black);


///1 point 1.3C

Temp_point = t/1.3;
if(Time !=0 )
{
 if( ((Rev_Temp_Point - Temp_point) > 1) || ((Temp_point - Rev_Temp_Point ) > 1) )
 	{
 			LCD_DrawLine(X_Pos+Time,224-Rev_Temp_Point,X_Pos+Time,224-Temp_point,Red);
 	}
 else
 	{ LCD_SetPoint(X_Pos+Time, 224-(Temp_point), Red);}
  Rev_Temp_Point = Temp_point;
    }

else{ LCD_SetPoint(X_Pos+Time, 224-(Temp_point), Red);}
	 Rev_Temp_Point = Temp_point;



Delay(0xffffff);
Time++;
if (Time == 319) Time=0;
	
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
