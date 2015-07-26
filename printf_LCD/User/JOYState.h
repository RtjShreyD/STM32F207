#ifndef _JOYState_H
#define _JOYState_H

#include <stdio.h>
#include "stm32f2xx.h"
#include "config.h"
#include "lcd.h"
void JOYState_LED_GPIO_Init(void);
uint8_t Read_JOYState(void);
void Led_Toggle(uint8_t key);
extern void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str,uint16_t Color, uint16_t bkColor);
#endif /*_JOYState_H*/
