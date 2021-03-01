#ifndef __USART_H_
#define	__USART_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

char USART_Init(const long int baudrate);
void Write_USART(uint8_t a);
void Write_USART_String(char *a);
char UART_Init(const long int baudrate);
uint8_t Read_USART(void);
void Read_USART_String(char *Output, unsigned int length);

#endif	/* XC_HEADER_TEMPLATE_H */

