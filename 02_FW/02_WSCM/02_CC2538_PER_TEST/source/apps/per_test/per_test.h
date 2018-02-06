//*****************************************************************************
//! @file       per_test.h
//! @brief      PER test header file.
//!
//! Revised     $Date: 2014-01-10 16:59:35 +0100 (fr, 10 jan 2014) $
//! Revision    $Revision: 11718 $
//
//  Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//****************************************************************************/
#ifndef __PER_TEST_H__
#define __PER_TEST_H__


/******************************************************************************
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************************************
* INCLUDES
*/


/******************************************************************************
* TYPEDEFS
*/
// PER test configuration
typedef struct
{
    unsigned char mode;             //!< PER test mode. [RX|TX]
    unsigned char state;            //!< PER test state (idle, transmit)
    unsigned char channel;          //!< PER test IEEE channel [11,26]
    unsigned char txPower;          //!< PER test TX power
    unsigned long burstSize;        //!< Number of packets to send in TX
    unsigned long pktRate;          //!< Number of packets per second
    unsigned char gainMode;         //!< Gain mode (CC2591 PA/LNA)
} perCfg_t;

// PER test packet format
typedef struct {
    unsigned long seqNumber;
    unsigned char padding[88];
} perTestPacket_t;

// PER test receiver statistics
typedef struct {
    unsigned long expectedSeqNum;
    unsigned long rcvdPkts;
    unsigned long lostPkts;
    signed short rssiSum;
} perRxStats_t;

/******************************************************************************
* CONSTANTS AND DEFINES
*/
// BasicRF definitions
#define PAN_ID                  0x2007
#define TX_ADDR                 0x2538
#define RX_ADDR                 0xBEEF
#define MAX_PAYLOAD_LENGTH      103
#define PACKET_SIZE             sizeof(perTestPacket_t)

#define RSSI_AVG_WINDOW_SIZE    32  // Window size for RSSI moving average

#define PER_MODE_TX             0
#define PER_MODE_RX             1

#define PER_GAIN_MODE_LO        0       // Same value as in hal_rf
#define PER_GAIN_MODE_HI        1       // Same value as in hal_rf
#define PER_GAIN_MODE_NONE      42

#define PER_TEST_VERSION        "v1.1.0 "


/******************************************************************************
* FUNCTION PROTOTYPES
*/
extern unsigned char appTransmitter(void);
extern unsigned char appReceiver(void);

/******************************************************************************
* GLOBAL VARIABLES
*/
extern perCfg_t perConfig;


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif // __PER_TEST_H__