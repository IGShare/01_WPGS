/*
 * IGS_WLGM_UART.h
 *
 * Created: 2018-04-09 오후 4:20:02
 *  Author: MINYOUNG EOM
 */ 


#ifndef IGS_WLGM_UART_H_
#define IGS_WLGM_UART_H_

#define BAUD							9600
#define MYUBRR							F_CPU/16/BAUD-1

void igs_wlgm_uart_init(void)
{
	uint32_t ubrr = MYUBRR;
	UBRR0H = (uint8_t)(ubrr >>8);
	UBRR0L = (uint8_t)(ubrr);
	
	// enable RX and TX and set interrupts on rx complete
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	// 8-bit, 1 stop bit, no parity, asynchronous UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (0 << USBS0) | (0 << UPM01) | (0 << UPM00) | (0 << UMSEL01) |	(0 << UMSEL00);

	UCSR0B |=  (1 << UDRIE0);

	// initialize the in and out buffer for the UART
	ring_buffer_out = ring_buffer_init(out_buffer, BUFFER_SIZE);
	ring_buffer_in = ring_buffer_init(in_buffer, BUFFER_SIZE);
}


/**
 * \brief Function for putting a char in the UART buffer
 *
 * \param data the data to add to the UART buffer and send
 *
 */
static inline void uart_putchar(uint8_t data)
{
	// Disable interrupts to get exclusive access to ring_buffer_out.
	cli();
	if (ring_buffer_is_empty(&ring_buffer_out)) {
		// First data in buffer, enable data ready interrupt
		UCSR0B |=  (1 << UDRIE0);
	}
	// Put data in buffer
	ring_buffer_put(&ring_buffer_out, data);

	// Re-enable interrupts
	sei();
}

/**
 * \brief Function for getting a char from the UART receive buffer
 *
 * \retval Next data byte in receive buffer
 */
static inline uint8_t uart_getchar(void)
{
	return ring_buffer_get(&ring_buffer_in);
}


/**
 * \brief Function to check if we have a char waiting in the UART receive buffer
 *
 * \retval true if data is waiting
 * \retval false if no data is waiting
 */
static inline bool uart_char_waiting(void)
{
	return !ring_buffer_is_empty(&ring_buffer_in);
}


#endif /* IGS_WLGM_UART_H_ */