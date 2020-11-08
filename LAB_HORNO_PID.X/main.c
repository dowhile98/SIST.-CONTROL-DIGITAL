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
#include "hardware_init.h"
#include "PID_HORNO.h"

/********************DEFINICION DE MACROS**************************************/
#define AN0                 0
#define AN1                 1

//PARAMETROS DE CONOTROL
#define KP                  2.637
#define KI                  0.659
#define KD                  2.367
#define TS                  0.1
/*******************DEFINICION DE VARIABLES GLOBALES***************************/
uint16_t data;          //LEER EL AN0
uint16_t dataRef;       //LEED EL AN1 TEMPERATURA DE REFERENCIA
uint16_t UartSetPoint;  //PARA EL SET POINT DEL UART
float temp;             //TEMPERATURA
float vout;             //VOLTAJE DE SALIDA DEL HORNO
float error;            //PARA CALCULAR EL ERROR
float Vin;              //VOLTAJE DE ENTRADA AL HORNO
float TempRef = 25;     //temperatura de referencia


/********************PROTOTIPO DE FUNCIONES************************************/
uint16_t readAdc_ANx(uint8_t anx);
void set_temp_ref(void);
/************************funcion prinicipal************************************/
int main(void) {
    Hardware_Init();
    LCD_Init(); //RS = RB6, RW = RB5, E = RB4
    PID_Init(KP,KI,KD,TS);
    printf("CONTROL PID - HORNO DE RESISTENCIA\r\n");
    delay_ms(0.1);
    LCD_print("  UNAC - FIEE");
    LCD_setCursor(1,0);//SE MUEVE A LA SEGUNDA FILA
    LCD_print("SIST. DE CONTROL");
    delay_ms(1500);
    set_temp_ref();         //SE ESTABLECE LA TEMPERATURA DE REFERENCIA
  
    while(1){
        LCD_clear();
        Oven_control(Vin);          //se establece el voltaje de entrada al horno
        if(PORTBbits.RB7){
            delay_ms(150);
            set_temp_ref();
        }
        LCD_clear();
        LCD_print("TEP. REF:");
        LCD_printFloat(TempRef);
        LCD_setCursor(1,0);
        LCD_print("TEMP HORNO:");
        LCD_printFloat(temp);
        printf("\ntemperatura del horno: %.2f C\r\n",temp);  
        printf("error................: %.2f C\r\n",error);
        printf("voltaje de entrada...: %.2f V\r\n",Vin);
        printf("voltaje de salida....: %.2f V\r\n",vout);
        
        delay_ms(100);
    }
}
void set_temp_ref(void){
    LATAbits.LATA4 = 0;
    while(1){
        LCD_clear();
        LCD_print("TEMP. REFERENCIA");
        dataRef = readAdc_ANx(AN1);
        TempRef = ((5.0/4095)*dataRef)/0.025;
        LCD_setCursor(1,0);
        LCD_print("temp: ");
        LCD_printFloat(TempRef);
        if(PORTBbits.RB7){
            delay_ms(100);
            while(PORTBbits.RB7);
            break;
        }
        delay_ms(50);
    }
    LATAbits.LATA4 = 1;
}

uint16_t readAdc_ANx(uint8_t anx){
    AD1CON1bits.ADON = 0;
    AD1CHS0bits.CH0SA = anx;  
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;
    delay_ms(0.01);
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete
    return ADC1BUF0;
}



//RUTINA DE SERIVICIO DE LA INTERRUPCION
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    data = readAdc_ANx(AN0);
    vout = (float)(5.0/4095)*data;
    temp = vout/0.025;
    error = 0.025*TempRef - vout;
    Vin = PID(error);
    
    
}
/*rutina de servicio de la interrupcion*/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;    //se borra el flag
    if(U1STAbits.URXDA){
        UartSetPoint = U1RXREG;
        printf("se recibio->%d\r\n",UartSetPoint);
     }
    
}
/*****************************************************************************
 *      ESTA FUNCION SIRVE PARA EL USO DE LA FUNCION PRINTF                  *
 ****************************************************************************/
void UART1_PutChar(char ch){
    while (U1STAbits.UTXBF == 1);
    U1TXREG = ch;
}
int    write(int handle, void *buffer, unsigned int len)
{
  int i;
   switch (handle)
  {
      case 0:        // handle 0 corresponds to stdout
      case 1:        // handle 1 corresponds to stdin
      case 2:        // handle 2 corresponds to stderr
      default:
          for (i=0; i<len; i++){
              UART1_PutChar(*(char*)buffer++);
          }
              
  }
  return(len);
}