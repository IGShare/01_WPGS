/*
 * IGS_WLGM_Function.h
 *
 * Created: 2018-04-08 오전 8:05:03
 *  Author: MINYOUNG EOM
 */ 


#ifndef IGS_WLGM_FUNCTION_H_
#define IGS_WLGM_FUNCTION_H_

void igs_wlgm_port_init()
{
	/* WSM STATUS PORT
	 * D20, D21, D22 STATUS 0,1,2 : PB0 PB1 PB2
	 * D23, D24		 STATUS 3,4   : PC4 PC5
	 * D25, D26, D27 STATUS 5,6,7 : PD5 PD6 PD7
	 * D28, D29		 STATUS 8,9   : PC0 PC1
	 */
	
	/* LED POSITION
	*  D27 D26 D21 D20 D25
	*  D24 D23 D29 D28 D22 
	*/
	
	DDRB = (0<<DDB7)|(0<<DDB6)|(0<<DDB5)|(0<<DDB4)|(0<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRC =			 (0<<DDC6)|(1<<DDC5)|(1<<DDC4)|(1<<DDC3)|(1<<DDC2)|(1<<DDC1)|(1<<DDC0);
	DDRD = (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(0<<DDD4)|(0<<DDD3)|(0<<DDD2)|(0<<DDD1)|(0<<DDD0);
	
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
}

void igs_wlgm_led_port_test()
{
	int i;
	for(i=0; i<2; i++){
		//Status LED Test (ON)
		PORTD &= ~(1<<PORTD7);_delay_ms(100);
		PORTD &= ~(1<<PORTD6);_delay_ms(100);
		PORTB &= ~(1<<PORTB1);_delay_ms(100);
		PORTB &= ~(1<<PORTB0);_delay_ms(100);
		PORTD &= ~(1<<PORTD5);_delay_ms(100);
		PORTB &= ~(1<<PORTB2);_delay_ms(100);
		PORTC &= ~(1<<PORTC0);_delay_ms(100);
		PORTC &= ~(1<<PORTC1);_delay_ms(100);
		PORTC &= ~(1<<PORTC4);_delay_ms(100);
		PORTC &= ~(1<<PORTC5);_delay_ms(100);
		
		//DP LED Test (GREEN OFF, RED ON)
		PORTC &= ~(1<<PORTC2);_delay_ms(100);
		PORTC |= (1<<PORTC3);_delay_ms(100);
		
		//Status LED Test (OFF)
		PORTD |= (1<<PORTD7);_delay_ms(100);
		PORTD |= (1<<PORTD6);_delay_ms(100);
		PORTB |= (1<<PORTB1);_delay_ms(100);
		PORTB |= (1<<PORTB0);_delay_ms(100);
		PORTD |= (1<<PORTD5);_delay_ms(100);
		PORTB |= (1<<PORTB2);_delay_ms(100);
		PORTC |= (1<<PORTC0);_delay_ms(100);
		PORTC |= (1<<PORTC1);_delay_ms(100);
		PORTC |= (1<<PORTC4);_delay_ms(100);
		PORTC |= (1<<PORTC5);_delay_ms(100);
		
		//DP LED Test (GREEN ON, RED OFF)
		PORTC |= (1<<PORTC2);_delay_ms(100);
		PORTC &= ~(1<<PORTC3);_delay_ms(100);
	}
	
		PORTD |= (1<<PORTD7);_delay_ms(100);
		PORTD |= (1<<PORTD6);_delay_ms(100);
		PORTB |= (1<<PORTB1);_delay_ms(100);
		PORTB |= (1<<PORTB0);_delay_ms(100);
		PORTD |= (1<<PORTD5);_delay_ms(100);
		PORTB |= (1<<PORTB2);_delay_ms(100);
		PORTC |= (1<<PORTC0);_delay_ms(100);
		PORTC |= (1<<PORTC1);_delay_ms(100);
		PORTC |= (1<<PORTC4);_delay_ms(100);
		PORTC |= (1<<PORTC5);_delay_ms(100);
		
		PORTC &= ~(1<<PORTC2);_delay_ms(100);
		PORTC &= ~(1<<PORTC3);_delay_ms(100);
}

void igs_wlgm_StatusInit()
{

	G_plcRxBitCnt		= 0;
	MYPPNSR				= 0;
	
	G_plcRxBuffer[0]	= 0;
	G_plcRxBuffer[1]	= 0;
	G_plcRxBuffer[2]	= 0;
	G_plcRxBuffer[3]	= 0;
	G_plcRxBuffer[4]	= 0;
	G_plcRxBuffer[5]	= 0;
}

void igs_wlgm_ExternalInterruptInit()
{
	EICRA  = (0 << ISC00);
	EICRA |= (1 << ISC01);    // set INT0 to trigger on Falling EDge
	EICRA |= (1 << ISC10);
	EICRA |= (1 << ISC11);    // set INT1 to trigger on Rising Edge
	
	EIMSK = (1 << INT0) | (1 << INT1);   // Turns on INT0 and INT1
}

void igs_wlgm_TimerZeroInit()
{
	TCCR0A = (0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
	TCCR0B = (0<<FOC0A) | (0<<FOC0B) | (0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
	TIMSK0 = (1<<TOIE0);
	TIFR0 = (1<<TOV0);
	//TCNT0 = TIMER_INIT_VALUE;
}

uint32_t igs_wlgm_ReadSerialNumber()
{
	uint8_t serialtmp[3];
	uint32_t serial;
	
	//eeprom_write_byte((uint8_t *)8, 0);
	
	serialtmp[0] = eeprom_read_byte((uint8_t *)4);
	serialtmp[1] = eeprom_read_byte((uint8_t *)5);
	serialtmp[2] = eeprom_read_byte((uint8_t *)6);
	
	serial = ((uint32_t)serialtmp[0] << 16) + ((uint32_t)serialtmp[1] << 8) + ((uint32_t)serialtmp[2]);
	return serial;
}

void igs_wlgm_SetControlIDCompleteResponse()
{
	uint8_t bitvalue=0;
	uint8_t mask = 0x01;
	uint8_t plcTxData=IDX_OPM_SET_ID_COMPLETE;
	
	
	//Start Bit
	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,mask);

	PLC_TX_ONE_BIT(0,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(1,PLC_TX_ONEBIT_TIME_US,plcTxData);
	PLC_TX_ONE_BIT(2,PLC_TX_ONEBIT_TIME_US,plcTxData);
	
	PORTD &= ~(1<<PORTD4);
}

#endif /* IGS_WLGM_FUNCTION_H_ */