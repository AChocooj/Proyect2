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
#define _XTAL_FREQ 4000000

//funciones
void configIO(void);

//uint8_t temperatura=0;
float tempera1=0;

char datos[20];


//puertos
void configIO(){
    TRISD=0;
    ANSEL=0;
    ANSELH=0;
    PORTD=0;
    
    INTCONbits.PEIE=1;
    PIE1bits.RCIE=1;
    PIR1bits.RCIF=0;
    INTCONbits.GIE=1;
    
}

void main(void) {
    configIO();
    uartRC_init(9600);
    I2C_Master_Init(100000);
   
    while(1){
     
       I2C_Master_Start();            // comunicacion con sensor
        I2C_Master_Write(0x39); //direccion de la comunicacion 
       __delay_ms(10);
        tempera1 = aht_GetTemperature();
        //enviar los datos por USART hacia la pc
       uartTX_Write_Str("T1   H1   \n");//enviar los datos del pic a la compu
       sprintf(datos, "%2.1f   %2.1f ", tempera1);//convertir los valores de voltaje y el contador a un string para que los lea bien la compu
      uartTX_Write(datos);//enviar el string con los valores a la pc
      uartTX_Write(13);//13 y 10 la secuencia es para dar un salto de linea 
      uartTX_Write(10);
        __delay_ms(10);
    }
    return;
}

