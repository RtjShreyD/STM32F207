#include "config.h"

void Open207_LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*--------------------------------------------------------------------------------
	
	LED GPIO Config
	
	--------------------------------------------------------------------------------*/
	/* GPIOF Periph clock enable */
	RCC_AHB1PeriphClockCmd(Open207Z_LED_GPIO_CLK, ENABLE);
	
	/* Configure PF6 PF7 PF8 PF9 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = Open207Z_GPIO_Pin_LED1 | Open207Z_GPIO_Pin_LED2
	 							  | Open207Z_GPIO_Pin_LED3 | Open207Z_GPIO_Pin_LED4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(Open207Z_LED_GPIO, &GPIO_InitStructure);
}
