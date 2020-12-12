
#include <p33FJ32MC204.h>

#include "hardware_config.h"

/* Protipo de funciones privadas*/
static void GPIO_Cofig(void);
static void TIM1_Config(void);
static void ADC_Config(void);
static void INTx_Config(void);
static void OCx_Config(void);
static void Uart_Config(void);

/* DEFINICICION DE FUNCIONES PRIVADAS PARA EL PROYECTO*/
static void GPIO_Cofig(void){
    AD1PCFGL = 0x1FF;       //TODOS LOS PINES ANALOGICOS
    TRISBbits.TRISB0 = 0;   //RB0->IN1
    TRISBbits.TRISB1 = 0;   //RB0->IN2
}
static void TIM1_Config(void){
    T1CON = 0;      //reset
    T1CONbits.TCKPS = 0b00;     //PSC->1
    TMR1 = 0;
    PR1 = 5000;                  //1ms
    /*configuracion de la interrupcion*/
    IPC0bits.T1IP = 2;          //prioridad 2
    IFS0bits.T1IF = 0;          //clear
}
static void ADC_Config(void){
    AD1CON1bits.AD12B = 1;  //se selecciona 12 bit
    AD1PCFGLbits.PCFG0 = 0; //AN0
    AD1PCFGLbits.PCFG1 = 0; //AN1
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
static void INTx_Config(void){
    TRISBbits.TRISB7 = 1;       //input
    INTCON2bits.INT0EP = 1;     //Interrupt on negative edge
    IPC0bits.INT0IP = 1;        //prioridad 1
    IFS0bits.INT0IF = 0;        //clear
    
}
static void OCx_Config(void){
    /*ASIGNACION DEL PIN*/
    RPOR1bits.RP2R = 0b10010;
    T2CON = 0;                  //se resetea la configuracion del timer2
    T2CONbits.TCKPS = 1;        //PSC->8
    PR2 = 4096;                 // PWM (152HZ)
    TMR2 = 0;   
    OC1CON = 0;                 //RESETEA TODO EL REGISTRO
    OC1R = 0;                   //Comparacion en 400ms
    OC1RS = 1;                  //Comparacion en 600ms
    OC1CONbits.OCM = 0b110;     //PMW
}
static void Uart_Config(void){
    RPOR6bits.RP12R = 3;   //RB12->tx
    RPINR18bits.U1RXR = 13;//RB13->RX
    U1MODE = 0;             //LIMPIO TODA LA CONFIGURACION
    U1STA = 0;              //LIMPIO TODA LA CONFIGURACION
    U1BRG = BRGVAL(9600);//SE ESTABLECE LA VELOCIDAD DE TRANSMISION
    
    IPC2bits.U1RXIP = 1;    //prioridad uno
    IFS0bits.U1RXIF = 0;    //se borra el flag
    IEC0bits.U1RXIE = 1;    //activas la interrupcion
    U1MODEbits.PDSEL = 0;   //TRANSMISION SIN PARIDAD
    U1MODEbits.STSEL = 0;   //BIT DE PARADA = 1
    U1MODEbits.UARTEN = 1;  //SE HABILITA EL MODULO UART1
    U1STAbits.UTXEN = 1;    //SE HABILITA LA TRANSMISION DE DATOS
}
/* definicion de funcion del archivo cabecera*/
void Hardware_Config(void){
    GPIO_Cofig();
    TIM1_Config();
    ADC_Config();
    OCx_Config();
    INTx_Config();
    Uart_Config();
    LCD_Init();
}

void Hardware_IT_Enable(void){
    __TIM1_IT_ENABLE();
    __TIM1_Enable_Count();
    __INT0_IT_ENABLE();
    __PWM1_Init();
}

static void UART1_PutChar(char ch){
    while (U1STAbits.UTXBF == 1);
    U1TXREG = ch;
}
//funcion para enviar datos al aurt
void UART1_printf(const char* str, ...)
{
  char stringArray[100];
  va_list args;
  va_start(args, str);
  vsprintf(stringArray, str, args);
  va_end(args);
  uint8_t i;
  for(i =0;  i<strlen(stringArray) && i<strlen(str); i++)
  {  
    UART1_PutChar((uint8_t)stringArray[i]);
  }
}