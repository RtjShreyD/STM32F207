#include "OneWire.h"
#include "systick.h"

void Onewire_Enable_GPIO_Port(void)
{
  DS18B20_RCC_AHB( DS18B20_PortRCC,ENABLE);
}

void Onewire_OUT_PULL_UP(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DS18B20_Port, &GPIO_InitStructure);	
}

void Onewire_OUT_FLOATING(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DS18B20_Port, &GPIO_InitStructure);
}

void Onewire_IN_FLOATING(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DS18B20_Port, &GPIO_InitStructure);	
}

void Onewire_IN_PULL_UP(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DS18B20_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DS18B20_Port, &GPIO_InitStructure);

}


/* Reset */
void resetOnewire(void) 
{
	Onewire_OUT_PULL_UP();
	CLR_DQ();
	delay_us(450);
	SET_DQ();
	delay_us(60);
	Onewire_IN_PULL_UP(); 
	delay_us(10);
	while(!(GET_DQ()));
	Onewire_OUT_PULL_UP();
	SET_DQ();
}
/* Read */
u8 rOnewire(void)
{
    u8 data=0,i=0;
    for(i=0;i<8;i++)
    {
		Onewire_OUT_PULL_UP();
		CLR_DQ();
		data=data>>1;
		SET_DQ();
		Onewire_IN_PULL_UP();
		delay_us(8);
		if(GET_DQ())data|=0x80;
		Onewire_OUT_PULL_UP();
		SET_DQ();
		delay_us(60);
    }
    return(data);
}

/* Write */
void wOnewire(u8 data)
{
	u8 i=0;
	Onewire_OUT_PULL_UP();
	SET_DQ();
	delay_us(16);
    	for(i=0;i<8;i++)
    	{
		CLR_DQ();
		if(data&0x01)
		{
			SET_DQ();
		}
   	 	else
   	 	{
			CLR_DQ();
    	}
    	data=data>>1;
		delay_us(40);  //65
		SET_DQ();
    }
}


