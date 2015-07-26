#ifndef _JOYState_H
#define _JOYState_H

#include <stdio.h>
#include "stm32f2xx.h"
#include "config.h"

void JOYState_LED_GPIO_Init(void);
uint8_t Read_JOYState(void);
void Led_Toggle(uint8_t key);

#endif /*_JOYState_H*/
