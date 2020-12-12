#ifndef __HARDWARE_CONFIG_H
#define __HARDWARE_CONFIG_H

#include "reloj.h"
#include "xlcd.h"

#include <libpic30.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/********** DEFINICION DE MACROS*********/
#define __TIM1_IT_ENABLE()      IEC0bits.T1IE = 1
#define __TIM1_IT_DISBLE()      IEC0bits.T1IE = 0
#define __INT0_IT_ENABLE()      IEC0bits.INT0IE = 1      
#define __INT0_IT_DISABLE()     IEC0bits.INT0IE = 0 
#define __UART1_RX_IT_ENABLE()  IEC0bits.U1RXIE = 1
#define __UART1_RX_IT_DISABLE() IEC0bits.U1RXIE = 0
  
#define __TIM1_Enable_Count()   T1CONbits.TON = 1
#define __TIM1_Disable_Count()  T1CONbits.TON = 0
#define __PWM1_Init()           T2CONbits.TON = 1

#define AN0                     0
#define AN1                     1
/* PROTOTIPO DE FUNCIONES***/

void Hardware_Config(void);
void Hardware_IT_Enable(void);

void UART1_printf(const char* str, ...);
#endif /*__HARDWARE_CONFIG_H*/