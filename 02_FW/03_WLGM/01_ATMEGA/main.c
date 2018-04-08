/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	status_bd_led_confirm();
	
	PORTB = (1<<PORTB2)|(1<<PORTB1)|(1<<PORTB0);
	PORTC = (1<<PORTC5)|(1<<PORTC4)|(1<<PORTC1)|(1<<PORTC0);
	PORTD = (1<<PORTD7)|(1<<PORTD6)|(1<<PORTD5);
	while(1);

	/* Insert application code here, after the board has been initialized. */
}
