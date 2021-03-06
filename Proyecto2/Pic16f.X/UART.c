/*
 * File:   UART.c
 * Author: jotas
 *
 * Created on February 9, 2020, 2:36 PM
 */


#include <xc.h>
#include "UART.h"
#define _XTAL_FREQ 4000000

uint8_t uartRC_init(uint16_t baudrate){
    uint16_t n;
    n = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
    if (n > 255){
        n = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
        TXSTAbits.BRGH = 1;
    }
    if (n < 256){
        SPBRG = n;
        TXSTAbits.SYNC = 0;
        RCSTAbits.SPEN = 1;
        RCSTAbits.CREN = 1;
        TXSTAbits.TXEN = 1;
    }
    return 0;
}


char uartRC_Read(){
    __delay_ms(5);
    uint8_t lectura = RCREG;
}

void uartTX_Write(char dato){
        TXREG = dato;
        while(TXSTAbits.TRMT == 0){
            __delay_us(500);
    }
}

void uartTX_Write_Str(char * string){
    int n;
    for (n=0; string[n] != '\n'; n++){
        uartTX_Write(string[n]);
    }
}