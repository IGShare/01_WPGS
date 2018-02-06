/*
 * Function.h
 *
 * Created: 2016-11-24 오후 2:33:58
 *  Author: myeom
 */ 


#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Global.h"

void SCMTF_PortInit()
{
	// Port Direction
	
	DDRB = (0<<DDB7)|(1<<DDB6)|(1<<DDB5)|(1<<DDB4)|(0<<DDB3)|(0<<DDB2)|(0<<DDB1)|(0<<DDB0);
	DDRD = (0<<DDD7)|(0<<DDD6)|(0<<DDD5)|(1<<DDD4)|(1<<DDD3)|(0<<DDD2)|(0<<DDD1)|(0<<DDD0);
	DDRE = (1<<DDE7)|(0<<DDE6)|(0<<DDE5)|(1<<DDE4)|(0<<DDE3)|(1<<DDE2)|(1<<DDE1)|(0<<DDE0);
	DDRF = (0<<DDF7)|(0<<DDF6)|(0<<DDF5)|(0<<DDF4)|(0<<DDF3)|(0<<DDF2)|(0<<DDF1)|(0<<DDF0);
	
	PORTB = (0<<PB7)|(1<<PB6)|(1<<PB5)|(1<<PB4)|(0<<PB3)|(0<<PB2)|(0<<PB1)|(0<<PB0);
	PORTE = (0<<PE7)|(0<<PE6)|(0<<PE5)|(0<<PE4)|(0<<PE3)|(1<<PE2)|(0<<PE1)|(0<<PE0);
	PORTD = (0<<PD7)|(0<<PD6)|(0<<PD5)|(1<<PD4)|(0<<PD3)|(0<<PD2)|(0<<PD1)|(0<<PD0);
	PORTF = (0<<PF7)|(0<<PF6)|(0<<PF5)|(0<<PF4)|(0<<PF3)|(0<<PF2)|(0<<PF1)|(0<<PF0);
	
}

void SCM485F_USART1Init()
{
	uint32_t ubrr = MYUBRR;
	UBRR1H = (uint8_t)(ubrr >>8);
	UBRR1L = (uint8_t)(ubrr);

	UCSR1C=(0<<UMSEL1)|(0<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10);
	//UCSR1B=(1<<RXCIE0)|(1<<RXEN1)|(1<<TXEN1)|(0<<UCSZ12);
	UCSR1B=(1<<RXEN1)|(1<<TXEN1);
}


//initialize buffer
void SCM485F_BufferInit(volatile u8buf *buf)
{
	buf->index = 0;
	buf->length = 0;
}

uint8_t SCM485F_OneByteWrite_485(volatile u8buf *buf, uint8_t u8data)
{
	
	if(buf->index < MAX_BUF_SIZE)
	{
		buf->buffer[buf->index] = u8data;
		buf->index++;
		return WRITE_OK;
	}
	else
	return WRITE_FAIL;
}


uint8_t SCM485F_OneByteRead_485(volatile u8buf *buf, volatile uint8_t *u8data)
{

	if(buf->index < buf->length )
	{
		*u8data=buf->buffer[buf->index];
		buf->index++;
	}

	if(buf->index == buf->length)
	return 1;
	else
	return 0;
}


#endif /* FUNCTION_H_ */