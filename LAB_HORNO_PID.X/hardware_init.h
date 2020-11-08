#ifndef __H_INIT
#define __H_INIT

#include <xc.h>
#include "reloj.h"
#include <libpic30.h>

void TIMER_Cofig(void);
void GPIO_Init(void);
void ADC_Config(void);
void Hardware_Init(void);
void PWM_Init(void);
void UART1_Init(uint16_t BaudRate);

#endif /*__H_INIT*/