#include "LIB_Config.h"
#include <math.h>

#define AVCC_mv 3300.0
#define Resistor 1000 //1Kohm


extern __IO uint16_t ADCConvertedValue;

void logo_display(u16 delayms);
int main(void) 
{
	float r,t;
	system_init();

	ssd1306_clear_screen(0x00);
	logo_display(1000);
	
	
	while(1){
//	ssd1306_clear_screen(0xFF);
//	delay_ms(1000);
//	ssd1306_clear_screen(0x00);
//	ssd1306_display_string(18, 0, "1.3inch OLED", 16, 1);
//	ssd1306_display_string(0, 16, "This is a demo for SSD1306/1106 OLED moudle!", 16, 1);
//	ssd1306_refresh_gram();
//	delay_ms(1000);

	

//	ssd1306_draw_bitmap(0, 2, &c_chSingal816[0], 16, 8);
//	ssd1306_draw_bitmap(24, 2, &c_chBluetooth88[0], 8, 8);
//	ssd1306_draw_bitmap(40, 2, &c_chMsg816[0], 16, 8);
//	ssd1306_draw_bitmap(64, 2, &c_chGPRS88[0], 8, 8);
//	ssd1306_draw_bitmap(90, 2, &c_chAlarm88[0], 8, 8);
//	ssd1306_draw_bitmap(112, 2, &c_chBat816[0], 16, 8);
	
	
//	ssd1306_draw_3216char(0,16, '2');
//	ssd1306_draw_3216char(16,16, '3');
//	ssd1306_draw_3216char(32,16, ':');
//	ssd1306_draw_3216char(48,16, '5');
//	ssd1306_draw_3216char(64,16, '6');
//	ssd1306_draw_1616char(80,32, ':');
//	ssd1306_draw_1616char(96,32, '4');
//	ssd1306_draw_1616char(112,32, '7');
//	ssd1306_draw_bitmap(87, 16, &c_chBmp4016[0], 40, 16);

//	ssd1306_display_string(0, 52, "MUSIC", 12, 0);
//	ssd1306_display_string(52, 52, "MENU", 12, 0);
	//ssd1306_display_string(98, 52, "PHONE", 12, 0);

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
	r= Resistor /((AVCC_mv/ADCConvertedValue)-1.0);
	t=1.0/(log(r/1000)/3950+(1.0/(25.0+273.0))) - 273;
	ssd1306_display_num(2,50,(unsigned int)t,3,16);
	ssd1306_display_char(26,53,'.',12,1);
	ssd1306_display_num(30,50,(unsigned long)(t*100)-((unsigned char)t*100),2,16);
	ssd1306_display_char(47,50,'C',12,1);
	ssd1306_refresh_gram();
	delay_ms(100);

	

	


	}
/*
	while (1) {

		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
		delay_ms(1000);
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
		delay_ms(1000);

	}
	*/
}


//Display Logo
void logo_display(u16 delayms)
{
	uint8_t x=0, y=0, p;
	volatile uint8_t y_pos=0;
	uint8_t chTemp = 0,  chMode = 0;
	uint16_t logo_size =0,cnt=0;

	for(y=0; y<6;y++)
	{
		y_pos=y*8;
		for (x = 0; x < 128; x ++) 
		{
			chTemp = img[cnt];
			for (p = 0; p <=8; p++) 
			{
				chMode = chTemp & 0x80? 1 : 0; 
				ssd1306_draw_point(x,y_pos+p, chMode);//chMode
				chTemp <<= 1;
							
			}
			cnt++;			
		}
		ssd1306_refresh_gram();		
	}


	delay_ms(delayms);
	


	
}


/*-------------------------------END OF FILE-------------------------------*/

