/*
 * IGS_WLGM_Global.h
 *
 * Created: 2018-04-08 오전 8:37:46
 *  Author: MINYOUNG EOM
 */ 


#ifndef IGS_WLGM_GLOBAL_H_
#define IGS_WLGM_GLOBAL_H_

uint32_t		mySerialNumber			= 0;
uint32_t		rxSerialNumber			= 0;
uint8_t			MY_ID					= 0;
uint8_t			EPR_ID					= 0;
uint8_t			SN_ReceiveSuccessRisingF	=0;
uint8_t			SN_ReceiveSuccessFallingF   =0;

struct TypeZeroPacket
{
	uint8_t	SerialNumber[3];
	uint8_t		controlID;
};
struct TypeOnePacket
{
	uint8_t		controlID;
	uint8_t		OperationMode;
	uint8_t		data;
};

struct TxPacket
{
	uint8_t		mode;
	uint8_t		sensor_status;
};

volatile uint8_t G_plcRxBuffer[6];
volatile uint8_t G_plcRxBitCnt=0;
volatile uint8_t G_RisingF = 0;
volatile uint8_t G_FallingF = 0;

volatile uint8_t G_preBitValue = 0;
volatile uint8_t LEDF = 0;

volatile uint8_t G_isSameValue = 0;


uint8_t out_buffer[BUFFER_SIZE];
uint8_t in_buffer[BUFFER_SIZE];

//! ring buffer to use for the UART transmission
struct ring_buffer ring_buffer_out;
//! ring buffer to use for the UART reception
struct ring_buffer ring_buffer_in;

#endif /* IGS_WLGM_GLOBAL_H_ */