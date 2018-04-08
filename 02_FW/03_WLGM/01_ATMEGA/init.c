/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	/* WSM STATUS PORT
	 * STATUS 0,1,2 : PB0 PB1 PB2
	 * STATUS 3,4   : PC4 PC5
	 * STATUS 5,6,7 : PD5 PD6 PD7
	 * STATUS 8,9   : PC0 PC1
	 */
	
	DDRB = (0<<DDB7)|(0<<DDB6)|(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRC =			 (0<<DDC6)|(1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(1<<DDC2)|(1<<DDC1)|(1<<DDC0);
	DDRD = (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(0<<DDD4)|(0<<DDD3)|(0<<DDD2)|(0<<DDD1)|(0<<DDD0);
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
}

void status_bd_led_confirm(void)
{
	PORTB = (1<<PORTB2)|(1<<PORTB1)|(1<<PORTB0);
	PORTC = (1<<PORTC5)|(1<<PORTC4)|(1<<PORTC1)|(1<<PORTC0);
	PORTD = (1<<PORTD7)|(1<<PORTD6)|(1<<PORTD5);
}
