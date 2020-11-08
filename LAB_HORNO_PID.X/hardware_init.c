#include "hardware_init.h"


/***********************DEFINCION DE FUNCIONES**********************************/
void Hardware_Init(void){
    TIMER_Cofig();
    GPIO_Init();
    ADC_Config();
    PWM_Init();
    UART1_Init(9600);
}
void TIMER_Cofig(void){
    T1CON = 0;
    T1CONbits.TCKPS = 0x2;          //PSC->64
    PR1 = 7812-1;                   //100ms
    //INTERRUPCIONES DEL TIMER
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 1;              //PRIORIDAD 1
    IEC0bits.T1IE = 1;              //SE ACTIVA LA INTERRUPCION POR TIMER
    
    T1CONbits.TON = 1;              //SE ACTIVA EL CONTEO
}
void GPIO_Init(void){
    TRISBbits.TRISB7 = 1;           //ENTRADA
    TRISAbits.TRISA4 = 0;           //SALIDA
}   
void ADC_Config(void){
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
void PWM_Init(void){
    /*ASIGNACION DEL PIN*/
    RPOR4bits.RP8R = 0b10010;
    T2CON = 0;                  //se resetea la configuracion del timer2
    T2CONbits.TCKPS = 2;        //PSC->64
    PR2 = 1301;                // PWM (60HZ)
    TMR2 = 0;   
    OC1CON = 0;                 //RESETEA TODO EL REGISTRO
    OC1R = 0;                   //Comparacion en 400ms
    OC1RS = 1;                  //Comparacion en 600ms
    OC1CONbits.OCM = 0b110;     //PMW
    
}

/*DEFINICION DE FUNCIONES*/
void UART1_Init(uint16_t BaudRate){
    RPOR6bits.RP12R = 3;    //RB12->tx
    RPINR18bits.U1RXR = 13; //RB13->RX
    U1MODE = 0;             //LIMPIO TODA LA CONFIGURACION
    U1STA = 0;              //LIMPIO TODA LA CONFIGURACION
    U1BRG = BRGVAL(BaudRate);//SE ESTABLECE LA VELOCIDAD DE TRANSMISION
    
    IPC2bits.U1RXIP = 1;    //prioridad uno
    IFS0bits.U1RXIF = 0;    //se borra el flag
    IEC0bits.U1RXIE = 1;    //activas la interrupcion
    U1MODEbits.PDSEL = 0;   //TRANSMISION SIN PARIDAD
    U1MODEbits.STSEL = 0;   //BIT DE PARADA = 1
    U1MODEbits.UARTEN = 1;  //SE HABILITA EL MODULO UART1
    U1STAbits.UTXEN = 1;    //SE HABILITA LA TRANSMISION DE DATOS
    
}