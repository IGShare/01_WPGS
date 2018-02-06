/*
 * UartTest.cpp
 *
 * Created: 2016-11-24 오후 2:33:00
 * Author : myeom
 */ 

#include <avr/io.h>
#include "Function.h"


#include <avr/interrupt.h>
#include <util/delay.h>


#include "Global.h"

unsigned char USART_Receive(void)
{
	while(!(UCSR1A & (1<<RXC1)))
		if(G_led4F == 0)
		{
		PORTB &= ~(1<<PB4);
		G_led4F = 1;
		_delay_us(100000*8);
		
		}
		else{
		PORTB |= (1<<PB4);
		G_led4F = 0;
		_delay_us(100000*8);
		}	
	return UDR1;
}

unsigned char USART_Transmit(unsigned char data)
{
	while(!(UCSR1A & (1<<UDRE1)))
			if(G_led5F == 0)
			{
			PORTB &= ~(1<<PB5);
			G_led5F = 1;
			_delay_us(100000*8);
			
			}
			else{
			PORTB |= (1<<PB5);
			G_led5F = 0;
			_delay_us(100000*8);
			}
	UDR1 = data;
}
int main(void)
{
    /* Replace with your application code */
	SCMTF_PortInit();
	SCM485F_USART1Init();
	SCM485F_BufferInit(&G_txBuf485_two);
	PORTB |= (1<<PB4);
	PORTB |= (1<<PB5);
	PORTB |= (1<<PB6);
	
	sei();
	
	unsigned char rdata;
    while (1) 
    {
		rdata = USART_Receive();
		USART_Transmit(rdata);
		
		//if(G_led4F == 0)
		//{
			//PORTB &= ~(1<<PB4);
			//G_led4F = 1;
			//_delay_us(100000*8);
						//
		//}
		//else{
			//PORTB |= (1<<PB4);
			//G_led4F = 0;
			//_delay_us(100000*8);
		//}
		
		/*
		if(G_rxCompleteF == 1)
		{

	
			G_txBuf485_two.length=G_rxBuf485_two.length;
			for(int i=0; i<G_rxBuf485_two.length; i++)
			{
				G_txBuf485_two.buffer[i]=0x55;

			}
			PORTD &= ~(1<<PD4); // Tx : PD4 low / Rx : PD4 hi
			//UCSR1B &= ~(1<<RXCIE1);
			UCSR1B |=  (1<<UDRIE1);
			
		}
		*/
    }
}


/*
ISR(USART1_RX_vect)
{
	//PORTB |= (1<<PB4);
	//PORTB |= (1<<PB5);
	//PORTB |= (1<<PB6);
	
	u8data = UDR1;
	if(WRITE_FAIL == SCM485F_OneByteWrite_485(&G_rxBuf485_two, u8data))
	{
		// ERROR :: 485 Rx buffer overFlow
		SCM485F_BufferInit(&G_rxBuf485_two);
	}
	else{
		G_rxCompleteF= 1;
	}

}
ISR(USART1_UDRE_vect)
{
	if(SCM485F_OneByteRead_485(&G_txBuf485_two, &UDR1) == 1)
	{
		UCSR1B &= ~(1<<UDRIE1);
		//UCSR1B |= (1<<TXCIE1);
					if(G_led5F == 0)
					{
						PORTB &= ~(1<<PB5);
						G_led5F = 1;
						_delay_us(100000*8);
						
					}
					else{
						PORTB |= (1<<PB5);
						G_led5F = 0;
						_delay_us(100000*8);
					}
		G_rxCompleteF = 0;
	}
}
ISR(USART1_TX_vect)
{
	PORTB &= ~(1<<PB6);
	//UCSR1B &= ~(1<<TXCIE1);
	PORTD |= (1<<PD4); // Tx : PD4 low / Rx : PD4 high
}

*/