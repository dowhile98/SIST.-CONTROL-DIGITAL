/*
 * File:   main.c
 * Author: Lenovo
 *
 * Created on 11 de diciembre de 2020, 01:04 AM
 */
#include "config.h"
#include "hardware_config.h"
#include <math.h>

/*definicion de macros*/
#define S           360             //sensibilidad del sensor
#define t           1               //1s de muestreo
#define Vo          1.65            //1.65v->0A
#define m           185             //sensibilidad = 185mV/A
#define K1          -0.0102
#define K2          -2.5518
#define Ko          0.0739
/*definicion de variables globales*/
uint16_t data;
float Vin;                          //VOUT->sensor
float I;                            //corriente que circula por el motor
uint16_t rpm;
float    radS;
volatile uint16_t count;
volatile uint32_t tick;

//VARIABLES PARA EL CONTROL

float Uk;
float r = 10;
/*******DEFINICION DE PROTOTIPO DE FUNCIONES*/
uint16_t readAdc_ANx(uint8_t anx);
void set_uk(void);

int main(void) {
    Hardware_Config();
    
    LCD_clear();
    LCD_printf("SIST. CONTROL");
    UART1_printf("CONFIGURACION EXITOSA\r\n");
    LCD_setCursor(1,0);
    LCD_printf("LAB 3 - PARTE 2");
    
    __delay_ms(500);
    LCD_clear();
    TRISBbits.TRISB4 = 0;
    LATBbits.LATB0 = 1;
    LATBbits.LATB1 = 0;
    Hardware_IT_Enable();
    while(1){
        r = (float)readAdc_ANx(AN1)*(15.0/4095);
        LCD_clear();
        LCD_printf("W:%.1f rad/s RPM",radS);
        LCD_setCursor(1,0);
        LCD_printf("I:%.1f uA  %d",1000000*I,rpm);
        __delay_ms(100);
    }
}
/*****************RUTINAS DE INTERRUPCION**************/
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;
    LATBbits.LATB4 ^=1;
    tick++;
    if(tick == 10){                     //cada 10ms
        //se lee el sensor ACS712 
        data = readAdc_ANx(AN0);
        Vin = (float)data * (3.3 / 4095);      //se halla el VOUT
        I = fabsf((Vin-Vo)/m);                 //se halla la corriente
        set_uk();
    }
    else if(tick == 1000){                   //cada 1000ms
        rpm  = count*60/((t)*(S));      //se calcula el rpm
        radS = (float)rpm*(2*3.1415)/60;//se calcula la velo en rad/s
        count = 0;                      //reset
        tick = 0;                       //reset
    }
}
//INT1
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void){
    IFS0bits.INT0IF = 0;
    count++;                //se incrementa en 1 en cada pulso
}
//UART1-> RX
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;    //se borra el flag
}
/*******FUNCION DE LECTURA ADC********************/
/* LECTURA ADC*/
uint16_t readAdc_ANx(uint8_t anx){
    AD1CON1bits.ADON = 0;
    AD1CHS0bits.CH0SA = anx;  
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;
    delay_ms(0.001);            //1us
    AD1CON1bits.SAMP = 0;
    while (!AD1CON1bits.DONE); // Wait for the conversion to complete
    return ADC1BUF0;
}

//definicion de la funcion de control
void set_uk(void){
    /* u(k) = Ko*r - K*x  **/
    Uk = Ko*r - (K1*radS + K2*I);
    float duty = Uk*4096.0/3.3 + 1;
    OC1RS = (uint16_t)duty ;
}