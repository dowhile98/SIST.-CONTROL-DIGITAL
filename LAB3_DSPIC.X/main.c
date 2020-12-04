/*
 * File:   main.c
 * Author: Lenovo
 *
 * Created on 4 de diciembre de 2020, 01:16 PM
 */


#include "config.h"
#include "reloj.h"
#include "xlcd.h"
#include <libpic30.h>

/****DEFINICION DE MACROS*******/
#define TIM1_Enable_Count()     T1CONbits.TON = 1
#define TIM1_Disable_Count()    T1CONbits.TON = 0
#define S                       20
#define PWM1_Init()             T2CONbits.TON = 1;
#define AN0                     0
/*******DEFINICION DE VARIABLES*****/
uint16_t count = 0;
uint16_t rpm;
float    radS;
uint16_t data;
/********DEFINCION DE PROTOTIPO DE FUNCIONES*******/
static void TIM1_Config_IT(void);
static void INT1_Config_IT(void);
static void Hardware_Init(void);
static void GPIO_Config(void);
static void OC_Config(void);
static void ADC_Init(void);
static uint16_t readAdc_ANx(uint8_t anx);
int main(void) {
    Hardware_Init();
    TRISBbits.TRISB15 = 0;
    
    LCD_print("hello world");
    LATAbits.LATA4 = 1;
    LATAbits.LATA1 = 0;
    TIM1_Enable_Count();
    PWM1_Init();            //configura el pwm
    
    while(1){   
        data = readAdc_ANx(AN0);
        OC1RS = data;
    }
    return 0;
}
/* LECTURA ADC*/
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
/*****RUTINAS DE SERVICIO DE INTERRUPCION*****/
//TIMER
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;
    rpm  = count*60/(S);
    radS = (float)rpm*(2*3.1415)/60;
    LATBbits.LATB15 ^=1;
    LCD_clear();
    LCD_print("P:");
    LCD_printInt(count);
    LCD_print("  rmp:");
    LCD_printInt(rpm);
    LCD_setCursor(1,0);
    LCD_printFloat(radS);
    LCD_print(" rad/s");
    
    count = 0;
    
}
//INT1
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void){
    IFS0bits.INT0IF = 0;
    count++;
}
/*******INICIALIZACION DE LOS PERIFERICOS NECESARIOS****/
static void Hardware_Init(void){
    ADC_Init();
    OC_Config();
    TIM1_Config_IT();
    INT1_Config_IT();
    GPIO_Config();
    LCD_Init();
}
/***********CONFIGURARION DEL TIMER, INT1, GPIO*****/
static void TIM1_Config_IT(void){
    T1CON = 0;      //reset
    T1CONbits.TCKPS = 0b11;     //PSC->256
    TMR1 = 0;
    PR1 = 19531;                //100ms
    /*configuracion de la interrupcion*/
    IPC0bits.T1IP = 2;          //prioridad 2
    IFS0bits.T1IF = 0;          //clear
    IEC0bits.T1IE = 1;          //enable interrupt
}
static void INT1_Config_IT(void){
    TRISBbits.TRISB7 = 1;       //input
    INTCON2bits.INT0EP = 1;     //Interrupt on negative edge
    IPC0bits.INT0IP = 1;        //prioridad 1
    IFS0bits.INT0IF = 0;        //clear
    IEC0bits.INT0IE = 1;        //interrup enable
}

static void GPIO_Config(void){
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA1 = 0;
}

static void OC_Config(void){
    /*ASIGNACION DEL PIN*/
    RPOR4bits.RP8R = 0b10010;
    T2CON = 0;                  //se resetea la configuracion del timer2
    T2CONbits.TCKPS = 1;        //PSC->8
    PR2 = 4096;                // PWM (152HZ)
    TMR2 = 0;   
    OC1CON = 0;                 //RESETEA TODO EL REGISTRO
    OC1R = 0;                   //Comparacion en 400ms
    OC1RS = 1;                  //Comparacion en 600ms
    OC1CONbits.OCM = 0b110;     //PMW
}

static void ADC_Init(void){
    AD1PCFGL = 0xFFFF;      //inicialmente se desactiva todas los pines adc
    AD1CON1bits.AD12B = 1;  //se selecciona 12 bit
    AD1PCFGLbits.PCFG0 = 0; //AN0
    AD1PCFGLbits.PCFG1 = 0; //AN0
    TRISAbits.TRISA0 = 1;   //entrada analogica
    TRISAbits.TRISA1 = 1;   //Entrada analogica
    AD1CON2bits.VCFG = 0;   //AVDD-AVss 
    AD1CON3bits.ADCS = 1;   //2 · TCY = TAD
    AD1CON2bits.CHPS = 0;   //= Converts CH0 and CH1
    AD1CON1bits.SSRC = 0;   //CONVERSION MANUAL
    AD1CON1bits.ASAM = 0;   //MUESTREO MUNUAL
    AD1CON1bits.FORM = 0;   //entero
    AD1CHS0bits.CH0NA = 0;  //0 = Channel 0 negative input is VREF
}