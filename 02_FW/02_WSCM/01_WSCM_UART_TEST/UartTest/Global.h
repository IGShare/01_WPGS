/*
 * Global.h
 *
 * Created: 2016-11-24 오후 2:40:40
 *  Author: myeom
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

//Version
#define VERSION							0x30

//Common
#define WRITE_OK						1
#define WRITE_FAIL						0

//Task Function
#define LOW								0
#define HIGH							1

#define TRUE							1
#define FALSE							0

#define ON								1
#define OFF								0


//RS 485 Function
#define BAUD							38400
#define F_CPU							8000000
#define MYUBRR							F_CPU/16/BAUD-1

#define MAX_BUF_SIZE					512
#define MAX_USM_LGM_SIZE				128
//RS 485
typedef struct{
	uint8_t  buffer[MAX_BUF_SIZE];
	uint16_t length;
	uint16_t index;
}u8buf;

volatile u8buf	G_rxBuf485, G_rxBuf485_two, G_txBuf485, G_txBuf485_two;
volatile uint8_t u8data;
volatile uint8_t G_rxCompleteF = 0;
volatile uint8_t G_led4F = 0, G_led5F = 0;




#endif /* GLOBAL_H_ */