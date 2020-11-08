/*
 * File:   main.c
 * Author: QUINO B. JEFFRY
 *
 * Created on 22 de octubre de 2020, 02:00 PM
 */

/**********************INCLUSION DE ARCHIVOS CABECERA**************************/
#include "config.h"
#include <libpic30.h>
#include "reloj.h"
#include "xlcd.h"
#include <stdio.h>

/********************DEFINICION DE MACROS**************************************/
#define SETPOINT            2.5
#define PIN_CONTROL         LATBbits.LATB8             
/*******************DEFINICION DE VARIABLES GLOBALES***************************/
uint16_t data;          //LEER EL ADC
float temp;             //TEMPERATURA
float val;
uint8_t tick;
/********************PROTOTIPO DE FUNCIONES************************************/
void TIMER_Cofig(void);
void GPIO_Init(void);
void ADC_Config(void);
void Hardware_Init(void);
/************************funcion prinicipal************************************/
int main(void) {
    Hardware_Init();
    LCD_Init(); //RS = RB6, RW = RB5, E = RB4
    delay_ms(0.1);
    printf("  UNAC - FIEE");
    LCD_setCursor(1,0);//SE MUEVE A LA SEGUNDA FILA
    printf("SIST. DE CONTROL");
    delay_ms(1500);
    LCD_clear();
    printf("**PRESS START**");
    LATAbits.LATA4 = 0;
    while(1){
        if(PORTBbits.RB7){
            delay_ms(100);
            while(PORTBbits.RB7);
            break;
        }
    }
    LATAbits.LATA4 = 1;
    while(1){
        
        val = (float)(5.0/4095)*data;
        temp = (1/0.025)*val;
        if(val < SETPOINT)
            PIN_CONTROL = 1;
        else
            PIN_CONTROL = 0;
        if(tick>=100){
            LCD_clear();
            printf("temp->%.1f",temp);
            LCD_setCursor(1,0);
            printf("val->%.2f",val);
            tick = 0;
        }
        delay_ms(1);
    }
}

/***********************DEFINCION DE FUNCIONES**********************************/
void Hardware_Init(void){
    TIMER_Cofig();
    GPIO_Init();
    ADC_Config();
    
    
}
void TIMER_Cofig(void){
    T1CON = 0;
    T1CONbits.TCKPS = 0x1;      //PSC->8
    PR1 = 625-1;                 //1ms
    //INTERRUPCIONES DEL TIMER
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 1;          //PRIORIDAD 1
    IEC0bits.T1IE = 1;          //SE ACTIVA LA INTERRUPCION POR TIMER
    
    T1CONbits.TON = 1;          //SE ACTIVA EL CONTEO
}
void GPIO_Init(void){
    TRISBbits.TRISB7 = 1;       //ENTRADA
    TRISBbits.TRISB8 = 0;       //SALIDA ->CONTROL
    TRISAbits.TRISA4 = 0;       //SALIDA
    
}   
void ADC_Config(void){
    AD1PCFGL = 0xFFFF;      //inicialmente se desactiva todas los pines adc
    /*0. Se selecciona 10-bit o 12-bit*/
    AD1CON1bits.AD12B = 1;  //se selecciona 12 bit
    /*1. Seleccione los pines del puerto como entradas analógicas (AD1PCFGH <15: 0> o AD1PCFGL <15: 0>).*/
    AD1PCFGLbits.PCFG0 = 0; //AN0
    TRISAbits.TRISA0 = 1;   //entrada analogica
    /*2. Seleccione la fuente de referencia de voltaje para que coincida con el rango 
     * esperado en las entradas analógicas (AD1CON2 <15:13>).*/
    AD1CON2bits.VCFG = 0;   //AVDD-AVss 
    /*3. Seleccione el reloj de conversión analógico para que coincida con la 
     * velocidad de datos deseada con el reloj del procesador (AD1CON3 <7: 0>).*/
    AD1CON3bits.ADCS = 1;   //2 · TCY = TAD
    /*4. Determine cuántos canales de muestreo y retención se utilizarán 
     * (AD1CON2 <9: 8> y AD1PCFGH <15: 0> o AD1PCFGL <15: 0>).*/
    AD1CON2bits.CHPS = 0;   
    /*5. Seleccione la muestra apropiada/secuencia de conversión (AD1CON1 <7: 5> y AD1CON3 <12: 8>).*/
    AD1CON1bits.SSRC = 0;  //CONVERSION MANUAL
    AD1CON1bits.ASAM = 1;  //MUESTREO AUTOMATICO
    /*6. Seleccione la forma en que se presentan los resultados de conversión 
     * en el búfer (AD1CON1 <9: 8>).*/
    AD1CON1bits.FORM = 0;   //enteros
    /*7. SELECCIÓN DE ENTRADA ANALÓGICA PARA CONVERSIÓN*/
    AD1CHS0bits.CH0SA = 0;  // Channel 0 positive input is AN0
    AD1CHS0bits.CH0NA = 0;  //0 = Channel 0 negative input is VREF
    /*8. Encienda el módulo ADC (AD1CON1 <15>).*/
    AD1CON1bits.ADON = 1;
    /*9. Configure la interrupción de ADC (si es necesario):
        a) Borrar el bit AD1IF.
        b) Seleccione la prioridad de interrupción de ADC.*/
}

//RUTINA DE SERIVICIO DE LA INTERRUPCION
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    tick++;
    AD1CON1bits.SAMP = 0; // Start converting
    while (!AD1CON1bits.DONE); // Conversion done?
    AD1CON1bits.DONE = 0; // Clear conversion done status bit
    data = ADC1BUF0;
}

/*****************************************************************************
 *      ESTA FUNCION SIRVE PARA EL USO DE LA FUNCION PRINTF                  *
 ****************************************************************************/
int    write(int handle, void *buffer, unsigned int len)
{
  int i;
   switch (handle)
  {
      case 0:        // handle 0 corresponds to stdout
      case 1:        // handle 1 corresponds to stdin
      case 2:        // handle 2 corresponds to stderr
      default:
          for (i=0; i<len; i++)
              
              WriteDataXLCD(*(char*)buffer++);
  }
  return(len);
}