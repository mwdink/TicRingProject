/*
 * stdioFixup.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: dinkem1
 *
 * 	Add support for printf
 */
#include "stdioFixup.hpp"
#include "uart.hpp"

FILE *uart_str;


///*!Function     usartInit
//*   \param      unsigned int baud
//*   \return     void
//*   \par Purpose
//*   			initialize the USART
//*   \note
//*/
//void
//usartInit(uint16_t baud)
//{
//	UCSR0A = (1 << U2X0);
//	baud = (F_CPU / 4 / baud - 1) / 2;
//
//	/*Set baud rate */
//	UBRR0H = (unsigned char)(baud>>8);
//	UBRR0L = (unsigned char)baud;
//
//	/* Enable receiver and transmitter */
//	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
//
//	/* Set frame format: 8data, 1stop bit */
//	UCSR0C = (3<<UCSZ00);
//}


/*!Function     setupStdIo
*   \param      none
*   \return     void
*   \par Purpose
*   			attach USART to stdio
*   \note
*/
void
setupStdIo(void)
{
	uart_str = fdevopen(uart_putchar, uart_getchar);
	stdout = stdin = uart_str;
}


///*!Function     uart_putchar
//*   \param      char data
//*   \param      FILE *stream
//*   \return     int
//*   \par Purpose
//*   			initialize the USART
//*   \note
//*/
//int
//uart_putchar (char data, FILE *stream)
//{
//	if (data == '\n')
//	{
//		uart_putchar('\r', stream);
//	}
//
//	/* Wait for empty transmit buffer */
//	while (!( UCSR0A & (1<<UDRE0)));
//
//    /* Put our character into the transmit buffer */
//	UDR0 = data;
//
//    return 0;
//}
//
//
//int
//uart_getchar (FILE *stream)
//{
//	return 0;
//}
//
//
//void
//usartTransmit(uint8_t data)
//{
//	/* Wait for empty transmit buffer */
//	while ( !( UCSR0A & (1<<UDRE0)));
//
//	/* Put data into buffer, sends the data */
//	UDR0 = data;
//}
