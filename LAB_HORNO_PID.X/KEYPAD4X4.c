#include "KEYPAD4X4.h"

/**************DFININICION DE VARIABLES GLOBLALES*******************************/
static const int8_t key_table [4][4]= {
                                        {'7','8','9','/'},
                                        {'4','5','6','X'},
                                        {'1','2','3','-'},
                                        {'c','0','=','+'}
                                       };

/***************+DEFINICIOJN DE FUNCIONES         *****************************/

void keypad_init(void){
    //FILAS
    R1_TRIS = 0;
    R2_TRIS = 0;
    R3_TRIS = 0;
    R4_TRIS = 0;
    //COLUMNAS
    C1_TRIS = 1;
    C2_TRIS = 1;
    C3_TRIS = 1;
    C4_TRIS = 1;
}

int8_t keypad_read(void){
    uint8_t row;
    int8_t col;
    uint8_t data;
    for(row = 0; row<4; row++){
        
        R1_LAT = 1;
        R2_LAT = 1;
        R3_LAT = 1;
        R4_LAT = 1;
        switch(row){
            case 0: R1_LAT = 0; break;
            case 1: R2_LAT = 0; break;
            case 2: R3_LAT = 0; break;
            case 3: R4_LAT = 0; break;
        }
        delay_ms(0.5);
        data = C4_PORT<<3 | C3_PORT<<2 | C2_PORT<<1 | C1_PORT<<0;
        col = KEYPAD_ERROR;
        switch(data){
            case 0xE: col = 0; break;
            case 0xD: col = 1; break;
            case 0xB: col = 2; break;
            case 0x7: col = 3; break;
        }
        if(col != KEYPAD_ERROR)
            break;      //salida del for
    }
    if(col == -1)
        return KEYPAD_ERROR;
    else
        return(key_table[row][col]);
    
}