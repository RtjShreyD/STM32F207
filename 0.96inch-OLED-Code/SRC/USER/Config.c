/**
  ******************************************************************************
  * @file    xxx.c 
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LIB_Config.h"
#include "stm32f10x_dma.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t ADCConvertedValue;



/* Private function prototypes -----------------------------------------------*/

static void device_init(void);
static void driver_init(void);
static void port_init(void);

static void adc1_init(void);


#ifdef INTERFACE_4WIRE_SPI
static void spi1_init(void);
#endif
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  System initialization.
  * @param  None
  * @retval  None
  */
void system_init(void)
{
	RCC_ClocksTypeDef tRCC;
	
	RCC_GetClocksFreq(&tRCC); 
	delay_init(tRCC.HCLK_Frequency);
	
    device_init();
    driver_init();
}


/**
 * @brief 
 * @param 
 * @retval 
 */
static void device_init(void)
{
	port_init();
#ifdef INTERFACE_4WIRE_SPI
	spi1_init();
#endif
	iic_init();
	adc1_init();
}

/**
  * @brief  driver initialization.
  * @param  None
  * @retval None
  */
static void driver_init(void)
{
	ssd1306_init();
}


static void port_init(void) 
{
	GPIO_InitTypeDef tGPIO;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); 
	
	/*----------------------------------------------------------------------------------*/
	//SPI
#ifdef INTERFACE_4WIRE_SPI
	tGPIO.GPIO_Pin = SSD1306_CLK_PIN;	 //SCK  MISO	MOSI		 		 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_AF_PP; 	
	GPIO_Init(GPIOA, &tGPIO);

	tGPIO.GPIO_Pin = SSD1306_DIN_PIN;  //SCK	MISO	MOSI				 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &tGPIO);

	
	
#elif defined(INTERFACE_3WIRE_SPI)
	tGPIO.GPIO_Pin = SSD1306_CLK_PIN;	 //SCK		 		 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(GPIOB, &tGPIO);
	
	tGPIO.GPIO_Pin = SSD1306_DIN_PIN;	 //MOSI		 		 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP; 	
	GPIO_Init(GPIOB, &tGPIO);
	
#endif
	
	
	/*----------------------------------------------------------------------------------*/
	
	//SSD1306 OLED
	tGPIO.GPIO_Pin = SSD1306_CS_PIN;     // CS				 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOB, &tGPIO);
	
	tGPIO.GPIO_Pin = SSD1306_RES_PIN;     // RES 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOB, &tGPIO);


	tGPIO.GPIO_Pin = SSD1306_DC_PIN;     // D/C 				 
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOB, &tGPIO);

	
	tGPIO.GPIO_Pin = GPIO_Pin_13;     
	tGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOC, &tGPIO);

	
	/*----------------------------------------------------------------------------------*/
	//I2C
#ifdef INTERFACE_IIC
	tGPIO.GPIO_Pin = IIC_SCL_PIN | IIC_SDA_PIN;
	tGPIO.GPIO_Mode = GPIO_Mode_Out_PP; //GPIO_Mode_Out_PP
	tGPIO.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &tGPIO);
#endif
	/*----------------------------------------------------------------------------------*/




}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	;
}


static void adc1_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	

	GPIO_InitTypeDef tGPIO;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/*------------------------------ADC GPIOA.01 ADC Enable ----------------------------*/
	tGPIO.GPIO_Pin = GPIO_Pin_1; //ADC1 - IN1 
	tGPIO.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&tGPIO);

	/*------------------------------ADC GPIOA.02 ADC Enable ----------------------------*/
	tGPIO.GPIO_Pin = GPIO_Pin_2; //ADC1 - IN1 
	tGPIO.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&tGPIO);

	

	//----------------------------DMA channel 1 Configuration-----------------/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((unsigned long)0x4001244C);
	DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned long)&ADCConvertedValue;
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
   /* ADC1 configuration ------------------------------------------------------*/
   ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStructure.ADC_ScanConvMode = DISABLE;
   ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfChannel = 1;
   ADC_Init(ADC1, &ADC_InitStructure);
 
   /* ADC1 regular channel1 configuration */ 
   ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
 
   /* Enable ADC1 DMA */
   ADC_DMACmd(ADC1, ENABLE);
   
   /* Enable ADC1 */
   ADC_Cmd(ADC1, ENABLE);
 
   /* Enable ADC1 reset calibration register */   
   ADC_ResetCalibration(ADC1);
   /* Check the end of ADC1 reset calibration register */
   while(ADC_GetResetCalibrationStatus(ADC1));
 
   /* Start ADC1 calibration */
   ADC_StartCalibration(ADC1);
   /* Check the end of ADC1 calibration */
   while(ADC_GetCalibrationStatus(ADC1));
      
   /* Start ADC1 Software Conversion */ 
   ADC_SoftwareStartConvCmd(ADC1, ENABLE);


   //ADC2 Configuration
   ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStructure.ADC_ScanConvMode = ENABLE;
   ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfChannel = 2;
   ADC_Init(ADC1,&ADC_InitStructure);

   // ADC1 regular channel1 configuration 
   ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);

    // Enable ADC1 
   ADC_Cmd(ADC1, ENABLE);

	   /* Enable ADC1 reset calibration register */   
   ADC_ResetCalibration(ADC1);
   /* Check the end of ADC1 reset calibration register */
   while(ADC_GetResetCalibrationStatus(ADC1));
 
   /* Start ADC1 calibration */
   ADC_StartCalibration(ADC1);
   /* Check the end of ADC1 calibration */
   while(ADC_GetCalibrationStatus(ADC1));
   




	
}




/**
  * @brief  SPI initialization.
  * @param  None
  * @retval None
  */
#ifdef INTERFACE_4WIRE_SPI
static void spi1_init(void)
{
	SPI_InitTypeDef tSPI;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	tSPI.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	tSPI.SPI_Mode = SPI_Mode_Master;		
	tSPI.SPI_DataSize = SPI_DataSize_8b;		
	tSPI.SPI_CPOL = SPI_CPOL_High;		
	tSPI.SPI_CPHA = SPI_CPHA_2Edge;	
	tSPI.SPI_NSS = SPI_NSS_Soft;		
	tSPI.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;		
	tSPI.SPI_FirstBit = SPI_FirstBit_MSB;	
	tSPI.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI1, &tSPI);  
 
	SPI_Cmd(SPI1, ENABLE); 
}
#endif



/*-------------------------------END OF FILE-------------------------------*/
