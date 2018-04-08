/*
 * IGS_WLGM_AT_V_0_1.cpp
 *
 * Created: 2018-04-08 오전 8:03:19
 * Author : MINYOUNG EOM
 */ 
#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#include "IGS_WLGM_Define.h"
#include "IGS_WLGM_Global.h"
#include "IGS_WLGM_Function.h"


int main(void)
{
    /* Replace with your application code */
	struct TypeOnePacket rx_message1;
	struct TxPacket tx_message;
	
	igs_wlgm_port_init();
	igs_wlgm_led_port_test();
	igs_wlgm_ExternalInterruptInit();
	igs_wlgm_TimerZeroInit();
	igs_wlgm_StatusInit();
	
	mySerialNumber = igs_wlgm_ReadSerialNumber();

	
	sei();

	while (1) 
    {

		if(G_isSameValue == 1){
			//PORTB ^= (1<<PB1);
			G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= G_preBitValue << (G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3));
			G_plcRxBitCnt++;
			G_isSameValue = 0;
		}
		if(G_plcRxBitCnt>=PLC_RX_MAXBIT){
			TCCR0B = (0<<CS02) | (0<<CS01) | (0<<CS00);
			
			uint8_t packetType =0;
			struct TypeZeroPacket rx_message0;

			packetType = (G_plcRxBuffer[0] & 0x0F)>>1;
			
			switch(packetType)
			{
				
				// CCM Mode
				// USM Control
				case IDX_PCLTYPE_ADDR_SET_START :{
					if(SN_ReceiveSuccessFallingF != 1){
						PORTC = PORTC &= ~(1<<PORTC2);
						PORTC = PORTC &= ~(1<<PORTC3);
					}
					break;
				}
				case IDX_PCLTYPE_CCM_USM_ADDR : {
					
					// Serial Number - Control ID Setting
					
					rxSerialNumber = ((uint32_t)(((G_plcRxBuffer[0]&0xF0) >> 4) | ((G_plcRxBuffer[1]&0x0F) << 4)) <<16)
					+((uint32_t)(((G_plcRxBuffer[1]&0xF0) >> 4) | ((G_plcRxBuffer[2]&0x0F) << 4)) <<8)
					+((( G_plcRxBuffer[2]&0xF0) >> 4) | ((G_plcRxBuffer[3]&0x0F) << 4));
					rx_message0.controlID		 = ((G_plcRxBuffer[3]&0xF0) >> 4) | ((G_plcRxBuffer[4]&0x0F) << 4);
					
					if(rxSerialNumber == mySerialNumber)
					{
						PORTC |= (1<<PORTC2);
						EPR_ID = eeprom_read_byte((uint8_t *)7);
						
						if(EPR_ID != rx_message0.controlID)
						{
							
							MY_ID = rx_message0.controlID;
							eeprom_write_byte((uint8_t *)7, rx_message0.controlID);
						}
						else
						{
							MY_ID = EPR_ID;
						}
						
						SN_ReceiveSuccessFallingF = 1;
						igs_wlgm_SetControlIDCompleteResponse();
					}
					break;
				}
				case IDX_PCLTYPE_CCM_USM_CNTL : {
					// USM Control
					
					if( SN_ReceiveSuccessFallingF == 1)
					{
						
						rx_message1.controlID = ((G_plcRxBuffer[0]&0xF0) >> 4) | ((G_plcRxBuffer[1] & 0x0F) << 4);
						rx_message1.OperationMode =  (G_plcRxBuffer[1]&0xF0) >> 4;
						rx_message1.data = G_plcRxBuffer[2];
						
						tx_message.sensor_status	= 0;

						if(rx_message1.controlID == MY_ID)
						{
							//PORTC = LED_GREEN_ON;
							//PORTC ^= (1<<PC3);
							//USMF_SensorOPMControl(rx_message1, &tx_message);
						}
					}
					//else
					//{
					//_delay_ms(12);
					//}
					break;
				}
				
				//SCM Mode
				case IDX_PCLTYPE_SCM_USM_CNTL : {
					//Sensor Control
					rx_message1.controlID = ((G_plcRxBuffer[0]&0xF0) >> 4) | ((G_plcRxBuffer[1] & 0x0F) << 4);
					rx_message1.OperationMode =  (G_plcRxBuffer[1]&0xF0) >> 4;
					rx_message1.data = G_plcRxBuffer[2];
					
					tx_message.sensor_status	= 0;

					if(rx_message1.controlID == EPR_ID)
					{
						//PORTC = LED_GREEN_ON;
						//USMF_SensorOPMControl(rx_message1, &tx_message);
					}
					break;
				}
			}
			igs_wlgm_StatusInit();
		}
	}
	
}


// 동일한 값이 오면 인터럽트 루틴을 타지 못하기 때문에 타이머로 체크
// SCM 에서 1bit time length 만큼의 시간으로 overflow interrupt를 발생시켜 주어야 한다.
ISR(TIMER0_OVF_vect)
{
	//PORTC ^= (1<<PC2);
	G_isSameValue = 1;
	TCNT0 = TIMER_INIT_VALUE;
}

//Start : Falling Edge
ISR (INT0_vect)
{
	TCCR0B = (0<<CS02) | (0<<CS01) | (0<<CS00);
	TCNT0 = TIMER_INIT_VALUE;
	TIFR0 &= ~(1<<TOV0);
	//PORTC ^= (1<<PC2);
	_delay_us(30);
	if(!(MYPPNSR & (1<<PPS)))//if(G_RisingF == 0)
	{
		MYPPNSR |= (1<<PNS);//G_FallingF = 1;
		G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= 1 <<(G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3)) ;
		G_preBitValue = 1;
		G_plcRxBitCnt++;
	}
	else
	{
		MYPPNSR &= ~(1<<PNS);//G_FallingF = 0;
		G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= 0 << (G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3));
		G_preBitValue = 0;
		G_plcRxBitCnt++;
	}
	
	//동일한 값이 오면 인터럽트 루틴을 타지 못하기 때문에 타이머로 체크
	
	TCCR0B = (0<<CS02) | (0<<CS01) | (1<<CS00);
	TCNT0 = TIMER_INIT_VALUE;
	TIFR0 = (1<<TOV0);
	

	EIFR  = (1<<INTF0) |(1<<INTF1);
}

//Start : Rising Edge
ISR (INT1_vect)
{
	TCCR0B = (0<<CS02) | (0<<CS01) | (0<<CS00);
	TCNT0 = TIMER_INIT_VALUE;
	TIFR0 &= ~(1<<TOV0);
	//PORTB ^= (1<<PB0);
	_delay_us(30);
	if(!(MYPPNSR & (1<<PNS)))//if(G_FallingF == 0)
	{
		MYPPNSR |= (1<<PPS);//G_RisingF = 1;
		G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= 1 << (G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3));
		G_preBitValue = 1;
		G_plcRxBitCnt++;
	}
	else
	{
		MYPPNSR &= ~(1<<PPS);//G_RisingF = 0;
		G_plcRxBuffer[(G_plcRxBitCnt>>3)] |= 0 << (G_plcRxBitCnt - ((G_plcRxBitCnt>>3) << 3));
		G_preBitValue = 0;
		G_plcRxBitCnt++;
	}
	
	TCCR0B = (0<<CS02) | (0<<CS01) | (1<<CS00);
	TCNT0 = TIMER_INIT_VALUE;
	TIFR0 = (1<<TOV0);
	

	EIFR  = (1<<INTF0) |(1<<INTF1);
}
