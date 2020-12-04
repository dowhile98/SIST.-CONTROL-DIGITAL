#ifndef XLCD_H
#define	XLCD_H


/**************************************************************************
 *  ESTOS PARAMETROS SE TIENEN QUE MODIFICAR A COMBENIENCIA               *
 * los pines usados para el manejo de datos tienes que ser pines continuos*
 * es por eso que se declara por puerto y on individualmente              *
 **************************************************************************/

#define DATA_PORT       PORTB                    //PARA EL PUERTO DE DATOS(D4-D7)
#define TRIS_DATA_PORT  TRISB

#define RW_PIN   LATBbits.LATB5                 /* PORT for RW */
#define TRIS_RW  TRISBbits.TRISB5               /* TRIS for RW */
#define RS_PIN   LATBbits.LATB6                 /* PORT for RS */
#define TRIS_RS  TRISBbits.TRISB6               /* TRIS for RS */
#define E_PIN    LATBbits.LATB4                 /* PORT for E  */
#define TRIS_E   TRISBbits.TRISB4               /* TRIS for E  */

#include <stdio.h>
#include "reloj.h"
/*****************************************************************************
 *          COMANDOS PARA EL MANEJO DEL DISPLAY                              *
 * ***************************************************************************/
#define DON         0b00001111  /* Display on      */
#define DOFF        0b00001011  /* Display off     */
#define CURSOR_ON   0b00001111  /* Cursor on       */
#define CURSOR_OFF  0b00001101  /* Cursor off      */
#define BLINK_ON    0b00001111  /* Cursor Blink    */
#define BLINK_OFF   0b00001110  /* Cursor No Blink */

/* Some Command Type defines							*/
#define CLEAR_XLCD		0x01		/* Clears the LCD		*/
#define RETURN_CURSOR_HOME	0x02		/* Returns the cursor to the HOME position	*/

/* Cursor or Display Shift defines */
#define SHIFT_CUR_LEFT    0b00010011  /* Cursor shifts to the left   */
#define SHIFT_CUR_RIGHT   0b00010111  /* Cursor shifts to the right  */
#define SHIFT_DISP_LEFT   0b00011011  /* Display shifts to the left  */
#define SHIFT_DISP_RIGHT  0b00011111  /* Display shifts to the right */

/* Function Set defines */
#define FOUR_BIT   0b00101111  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111111  /* 8-bit Interface               */
#define LINE_5X7   0b00110011  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110111  /* 5x10 characters               */
#define LINES_5X7  0b00111011  /* 5x7 characters, multiple line */
/* LINES*/
#define DDRAM_LINE1   0b10000000  /* 4-bit Interface               */
#define DDRAM_LINE2   0b11000000  /* 4-bit Interface               */
#define CGRAM_ADDRESS 0b01000000  /* 4-bit Interface               */

/*esta funcion inicializa la pantalla lcd*/
void LCD_Init(void);
/*se debe ingresar la fila y luego la columna*/
void LCD_setCursor(int x,int y);//<!fila - columna

void LCD_WriteChr_CGRAM( const char *buffer, unsigned char Addres);
/* OpenXLCD
 * Configures I/O pins for external LCD
 */
void OpenXLCD(unsigned char lcdtype);

/* SetCGRamAddr
 * Sets the character generator address
 */
void SetCGRamAddr(unsigned char);

/* SetDDRamAddr
 * Sets the display data address
 */
void SetDDRamAddr(unsigned char);

/* BusyXLCD
 * Returns the busy status of the LCD
 */
unsigned char BusyXLCD(void);

/* ReadAddrXLCD
 * Reads the current address
 */
unsigned char ReadAddrXLCD(void);

/* ReadDataXLCD
 * Reads a byte of data
 */
char ReadDataXLCD(void);

/* WriteCmdXLCD
 * Writes a command to the LCD
 */
void WriteCmdXLCD(unsigned char cmd);

/* WriteDataXLCD
 * Writes a data byte to the LCD
 */
void WriteDataXLCD(char);

/* putcXLCD
 * A putc is a write
 */
#define putcXLCD WriteDataXLCD

/* putsXLCD
 * Writes a string of characters to the LCD
 */
void LCD_print(char *);


extern void Delay_1us(void);   // 1us delay
extern void DelayPORXLCD(void);    // 15ms delay
extern void DelayXLCD(void); // 4.1ms
extern void DelayExecution(void);


/***********************************************************************
*ESTAS FUNCIONES SON AÑADIDAS NO SON ESCENCIALES PARA EL FUNCIONAMIENTO*
************************************************************************/
/*retorno de cursor al inicio*/
void LCD_setHome(void);
/*FUNCION PARA ENCENDER EL CURSOR DE LA LCD*/

void LCD_cursorOn(void);
/*funcion para desahabilitar el cursor de la lcd*/
void LCD_cursorOff(void);
/*funcion para limpiar la pantalla*/
void LCD_clear();
/*funcion para habilitar el blink del cursor lcd*/
void LCD_cursorBlinkOn(void);
/*funcion para desahabilitar el blink del cursor*/
void LCD_cursorBlinkOff(void);
/*funcion para mostrar un nunero entero */
void LCD_printInt(int number);
/*funcion para mostrar un numero flotante*/
void LCD_printFloat(double );

/**********************************************************/
/*funciones de desplazamiento*/
void LCD_shiftToRight(uint8_t num);

void LCD_shiftToLeft(uint8_t num);


#endif	/* XLCD_H */
