/*
 * uart.c
 *
 *  Created on: May 20, 2015
 *      Author: dexter
 *
 *      This code was tested on ATmega16u4 / ATmega32u4.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 256	// fixed value.

static volatile uint8_t txBuffer[TX_BUFFER_SIZE];
static volatile uint8_t txBufferIdx;
static volatile uint8_t txBufferCur;
static volatile uint8_t rxBuffer[RX_BUFFER_SIZE];
static volatile uint8_t rxBufferIdx;
static volatile uint8_t rxBufferCur;

ISR(USART1_UDRE_vect)
{
	uint8_t sreg=SREG;
	cli();

	if (txBufferIdx != txBufferCur) {
		UDR1 = txBuffer[txBufferCur];
		txBufferCur++;
	} else {
		UCSR1B = ((1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1));
	}

	SREG=sreg;
}

ISR(USART1_RX_vect)
{
	uint8_t sreg=SREG;
	cli();

	rxBuffer[rxBufferCur++] = UDR1;

	rxBufferIdx &= (RX_BUFFER_SIZE-1);

	SREG=sreg;
}

void uart_init(uint32_t baudrate)
{
	cli();

	UBRR1 = (F_CPU / 4 / baudrate - 1) / 2;
	UCSR1A = (1<<U2X1);
	UCSR1B = ((1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1));
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);

	txBufferIdx = txBufferCur = 0;
	rxBufferIdx = rxBufferCur = 0;

	sei();
}

void uart_put_string(const uint8_t *str, uint8_t size)
{
	uint8_t sreg=SREG;
	cli();

	while(size) {
		txBuffer[txBufferIdx++] = *str++;
		size--;
	}

	UCSR1B = ((1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1) | (1<<UDRIE1));

	SREG=sreg;
}

void uart_put_char(const uint8_t c)
{
	uint8_t sreg=SREG;
	cli();

	txBuffer[txBufferIdx++] = c;

	UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1) | (1<<UDRIE1);

	SREG=sreg;
}

uint8_t uart_get_char(void)
{
	if (rxBufferIdx == rxBufferCur) return 0;

	uint8_t c;
	uint8_t sreg=SREG;
	cli();

	c = rxBuffer[rxBufferIdx++];

	rxBufferIdx &= (RX_BUFFER_SIZE-1);

	SREG=sreg;

	return c;
}

uint8_t uart_available(void)
{
	uint8_t sreg=SREG;
	cli();

	uint8_t cur = rxBufferCur;
	uint8_t idx = rxBufferIdx;
	uint8_t r=0;

	if (idx-cur) {
		cur += RX_BUFFER_SIZE;
		r = (cur - idx);
	} else {
		r = (cur - idx);
	}

	SREG=sreg;

	return r;
}

void uart_rx_flush(void)
{
	rxBufferIdx = rxBufferCur = 0;
}
