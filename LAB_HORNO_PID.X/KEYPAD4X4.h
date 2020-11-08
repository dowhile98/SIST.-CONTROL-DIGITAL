#ifndef __KEYPAD4X4_H
#define __KEYPAD4X4_H

/*************************INCLUSION DE LIBRERIAS*******************************/
#include <stdint.h>
#include <xc.h>
#include "reloj.h"
#include <libpic30.h>
/**********************DEFINICION MACROS***************************************/

/**
 * Cambiar estos macros a conveniencia
 * de acuerdo a los pines usados en su proyecto
 */
//pines para las columnas
#define R1_TRIS     TRISBbits.TRISB9
#define R1_LAT      LATBbits.LATB9
#define R2_TRIS     TRISBbits.TRISB10
#define R2_LAT      LATBbits.LATB10
#define R3_TRIS     TRISBbits.TRISB11
#define R3_LAT      LATBbits.LATB11
#define R4_TRIS     TRISBbits.TRISB12
#define R4_LAT      LATBbits.LATB12
//pines para las comlumnas
#define C1_TRIS     TRISBbits.TRISB13
#define C1_PORT     PORTBbits.RB13
#define C2_TRIS     TRISBbits.TRISB14
#define C2_PORT     PORTBbits.RB14
#define C3_TRIS     TRISBbits.TRISB15
#define C3_PORT     PORTBbits.RB15
#define C4_TRIS     TRISAbits.TRISA3
#define C4_PORT     PORTAbits.RA3

//DEFINICION DE MACROS GENERICOS

#define KEYPAD_ERROR    -1

/*************************DEFINICION DE PROTOTIPO DE FUNCIONES*****************/
void keypad_init(void);
int8_t keypad_read(void);


#endif /* __KEYPAD4X4_H */