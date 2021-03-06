/*
 * File:   pic16f.c
 * Author: Allison Chocooj 
 *
 * Created on 25 de febrero de 2021, 05:47 PM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF       // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "I2C.h"
#include "USART.h"
#include "aht10.h"
#define _XTAL_FREQ 8000000

//funciones
void configIO(void);
char LecturaUSART=0;
uint8_t temperatura=0;
uint8_t humedad=0;
float tempera1=0;
float humeda1=0;


//puertos
void configIO(){
    TRISB=0;
    ANSEL=0;
    ANSELH=0;
    PORTB=0;
    
    INTCONbits.PEIE=1;
    PIE1bits.RCIE=1;
    PIR1bits.RCIF=0;
    INTCONbits.GIE=1;
    
}
void __interrupt() ISR(){
    if (RCIF==1){
        RCIF=0;
        LecturaUSART=Read_USART();
    }
}

void main(void) {
    configIO();
    USART_Init(9600);
    I2C_Master_Init(100000);
   
    while(1){
        Write_USART("a");
        Write_USART_String(aht_GetHumidity);
        Write_USART_String(aht_GetTemperature);
        __delay_ms(1000);
    }
    return;
}
