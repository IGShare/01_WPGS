/*
 * uart.h
 *
 *  Created on: May 20, 2015
 *      Author: dexter
 *
 *      This code was tested on ATmega16u4 / ATmega32u4.
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(uint32_t baudrate);

void uart_put_string(const uint8_t *str, uint8_t size);

void uart_put_char(const uint8_t c);

uint8_t uart_get_char(void);

uint8_t uart_available(void);

void uart_rx_flush(void);

#endif /* UART_H_ */
