//*****************************************************************************
//! @file       per_test.c
//! @brief      Packet Error Rate test for CC2538 on SmartRF06EB/BB.
//!
//!             CC2538/CC2592EM is supported on SmartRF06EB.
//!             The CC2538/CC2592EM only has access to LED1 and LED2, so the
//!             PER is not indicated by the LEDs when this module is selected.
//!             Instead LED1 is toggled as long as packets are received.
//!
//!             SmartRF06EB: Follow the instructions on the LCD display.
//!             SmartRF06BB: Press UP key to start/stop TX.
//!                          Press DOWN key to start RX. Reset PER statistics
//!                          by pressing SELECT key. LEDs indicate the current
//!                          PER as follows:
//!                          LED1 blinks if PER is >= 10%
//!                          LED2 blinks if PER is <  10%
//!                          LED3 blinks if PER is <   5%
//!                          LED4 blinks if PER is <   1%
//!                          To return from RX, power cycle CC2538.
//!
//! Revised     $Date: 2014-01-21 15:06:31 +0100 (ti, 21 jan 2014) $
//! Revision    $Revision: 11955 $
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


/**************************************************************************//**
* @addtogroup per_test
* @{
******************************************************************************/


/******************************************************************************
* INCLUDES
*/
#include "bsp.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "per_test.h"

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
#include "lcd_dogm128_6.h"
#include "per_test_menu.h"
#include "util_menu_driver.h"
#endif

#include "basic_rf.h"
#include "hal_rf.h"
#include "hal_timer_32k.h"
#include "hal_int.h"

#include "hw_cctest.h"


/******************************************************************************
* DEFINES
*/
#define PER_IDLE                0
#define PER_TRANSMIT            1
#define PER_NO_PACKET_RECEIVED  2
#define PER_PACKET_RECEIVED     3

#define PER_LED_UPDATE_RATE     16 // LED updates 16 times / sec


/******************************************************************************
* GLOBAL VARIABLES
*/
perCfg_t perConfig = {0};
#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
extern const char pLcdTiLogo[];  // TI splash screen
#endif


/******************************************************************************
* LOCAL VARIABLES
*/
static basicRfCfg_t basicRfConfig;
static perTestPacket_t tTxPacket;
static perTestPacket_t tRxPacket;

static uint8_t ucLedPer; // Holds integer PER value
static uint8_t ucLedBm;


/******************************************************************************
* LOCAL FUNCTION PROTOTYPES
*/
static void appTimerConfig(unsigned long ulIsrPerSecond);
static void appTimerIsr(void);
static void appActiveModeCleanup(void);
static void appLedReset(void);
static void appLedUpdate(void);
#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
static void appWriteLcdSplash(void);
static void appWriteLcdTxStatics(void);
static void appWriteLcdRxStatics(void);
#endif
#if (defined(BOARD_SMARTRF06BB) || defined(SMARTRF06BB))
static void appLedBlink(void);
#endif


/******************************************************************************
* FUNCTIONS
*/
/**************************************************************************//**
* @brief    PER test main function.
*
* @return   None
******************************************************************************/
int main(void)
{
    unsigned char keysPressed = 0;
    volatile unsigned long ulLoop;

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
    //
    // Set the first menu to be displayed by the menu driver
    //
    menu_t *pCurrentMenu = &startMenu;
#endif

    //
    // Initialize board
    //
    bspInit(BSP_SYS_CLK_SPD);

    //
    // Initialize keys and key interrupts
    //
    bspKeyInit(BSP_KEY_MODE_ISR);
    bspKeyIntEnable(BSP_KEY_ALL);

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
    //
    // Initialize SPI interface and LCD
    //
    bspSpiInit(BSP_SPI_CLK_SPD);
    lcdInit();

#elif (defined(BOARD_SMARTRF06BB) || defined(SMARTRF06BB))
    //
    // Blink LEDs to indicate life
    //
    appLedBlink();
#endif

    //
    // Set default configuration (used by SmartRF06 batteryboard)
    //
    perConfig.mode = PER_MODE_TX;
    perConfig.state = PER_IDLE;
    perConfig.channel = 26;
    perConfig.txPower = 0;          // Index 0. Max output
    perConfig.burstSize = 1000000;  // Max value
    perConfig.pktRate   = 20;       // 20 pkts per second
    perConfig.gainMode = PER_GAIN_MODE_NONE; // No PA/LNA

    //
    // Enable interrupts
    //
    halIntOn();

    //
    // Config basicRF
    //
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.ackRequest = false;

#if defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB)
    //
    // Print splash screen and wait for user input
    //
    appWriteLcdSplash();
    while(!bspKeyGetDir());

    //
    // Menu driver runs the show. The menu driver calls appTransceiver() or
    // appReceiver() based on user input.
    //
    while(1)
    {
        //
        // Display menu
        //
        menuDisplay(pCurrentMenu);

        //
        // Action?
        //
        keysPressed = bspKeyPushed(BSP_KEY_ALL);
        if(keysPressed & (BSP_KEY_RIGHT|BSP_KEY_SELECT)) {
            pCurrentMenu = menuEnter(pCurrentMenu);
        }
        else if(keysPressed & BSP_KEY_LEFT) {
            pCurrentMenu = menuBack(pCurrentMenu);
        }
        else if(keysPressed & BSP_KEY_UP) {
            menuUp(pCurrentMenu);
        }
        else if(keysPressed & BSP_KEY_DOWN) {
            menuDown(pCurrentMenu);
        }

        //
        // Simple wait
        //
        for(ulLoop=0; ulLoop<50000; ulLoop++);
    }
#elif defined(BOARD_SMARTRF06BB) || defined(SMARTRF06BB)
    //
    // SmartRF06BB
    //
    while(1)
    {
        //
        // Let user select mode
        //
        keysPressed = bspKeyPushed(BSP_KEY_ALL);
        if(keysPressed & BSP_KEY_UP) {
            appLedBlink();
            appTransmitter();
        }
        else if(keysPressed & BSP_KEY_DOWN) {
            appLedBlink();
            appReceiver();
        }
    }
#else
    while(1)
    {
        //
        // Error. We should never get here.
        //
    }
#endif
}


/**************************************************************************//**
* @brief    Function for handling active TX mode. Transmits the number of
*           packets specified by the user. Returns on user abort or when
*           packet transmit is completed.
*
* @return   None
******************************************************************************/
unsigned char appTransmitter(void)
{
    unsigned char n, ucKeyPressed;
    unsigned long pktsSent = 0;

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
    //
    // Setup static LCD content
    //
    appWriteLcdTxStatics();
#endif

    //
    // Initialize BasicRF
    //
    basicRfConfig.myAddr = TX_ADDR;
    basicRfConfig.channel = perConfig.channel;
    if(basicRfInit(&basicRfConfig) == FAILED)
    {
#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
        lcdBufferClearPart(0, 0,127, eLcdPage1, eLcdPage7);
        lcdBufferPrintString(0, "Failed to initialize", eLcdAlignCenter, eLcdPage3);
        lcdBufferPrintString(0, "BasicRF!", eLcdAlignCenter, eLcdPage4);
        lcdSendBufferPart(0, 0,127, eLcdPage3, eLcdPage4);
#endif
        while(1)
        {
        }
    }

    //
    // Turn receiver off
    //
    basicRfReceiveOff();
    perConfig.mode = PER_MODE_TX;
    perConfig.state = PER_IDLE;

    //
    // Set TX power as chosen by user
    //
    halRfSetTxPower(perConfig.txPower);

    //
    // Initialize packet payload
    //
    tTxPacket.seqNumber = 0;
    for(n = 0; n < sizeof(tTxPacket.padding); n++)
    {
        tTxPacket.padding[n] = n;
    }

    //
    // Configure packet interval timer
    //
    appTimerConfig(perConfig.pktRate);

    while(1)
    {
        ucKeyPressed = bspKeyGetDir();
        if(ucKeyPressed & BSP_KEY_EVT_SELECT) {
            //
            // Exit TX loop
            //
            break;
        }
        if(perConfig.state == PER_TRANSMIT)
        {
            if(pktsSent < perConfig.burstSize) {
                //
                // Make sure sequence number has network byte order
                //
                UINT32_HTON(tTxPacket.seqNumber);

                basicRfSendPacket(RX_ADDR, (unsigned char*)&tTxPacket, PACKET_SIZE);

                //
                // Change byte order back to host order before increment
                //
                UINT32_NTOH(tTxPacket.seqNumber);

                //
                // Update variables
                //
                tTxPacket.seqNumber++;
                pktsSent++;
                perConfig.state = PER_PACKET_RECEIVED;

                //
                // Update LED
                //
                bspLedToggle(BSP_LED_1);

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
                //
                // Update LCD
                //
                lcdBufferClearPart(0, 86,127, eLcdPage2, eLcdPage3);
                lcdBufferPrintInt(0, pktsSent, 92, eLcdPage2);
                lcdBufferPrintFloat(0, (float)(100*(pktsSent/((float)(perConfig.burstSize)))), 2, 92, eLcdPage3);
                lcdSendBufferPart(0, 86,127, eLcdPage2, eLcdPage3);
#endif
            }
            else {
                //
                // Done sending packets, exit TX loop
                //
                break;
            }
        }
    }

    //
    // Cleanup
    //
    appActiveModeCleanup();

    //
    // Return success
    //
    return 0;
}


/**************************************************************************//**
* @brief    Function for handling active RX mode.
*
* @return   None
******************************************************************************/
unsigned char appReceiver(void)
{
    //
    // Statistics variables
    //
    float fPacketErrorRate;
    perRxStats_t tRxStats = {0};
    signed short ssRssi;

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
    //
    // RSSI variables
    //
    signed short ssMovingAvgRssi;
    signed short pssRssiBuf[RSSI_AVG_WINDOW_SIZE] = {0};
    unsigned char ucRssiBufCounter = 0;

    //
    // Print statics to LCD
    //
    appWriteLcdRxStatics();
#endif

    //
    // Initialize BasicRF
    //
    basicRfConfig.myAddr = RX_ADDR;
    basicRfConfig.channel = perConfig.channel;
    if(basicRfInit(&basicRfConfig)==FAILED)
    {
#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
        lcdBufferClearPart(0, 0,127, eLcdPage1, eLcdPage7);
        lcdBufferPrintString(0, "Failed to initialize", eLcdAlignCenter, eLcdPage3);
        lcdBufferPrintString(0, "BasicRF!", eLcdAlignCenter, eLcdPage4);
        lcdSendBufferPart(0, 0,127, eLcdPage3, eLcdPage4);
#endif
        while(1)
        {
        }
    }

    //
    // Combo module?
    //
    if(perConfig.gainMode != PER_GAIN_MODE_NONE)
    {
        //
        // Set gain mode
        //
        halRfSetGain(perConfig.gainMode);
    }

    //
    // Set PER config flags
    //
    perConfig.mode = PER_MODE_RX;
    perConfig.state = PER_NO_PACKET_RECEIVED;

    //
    // Configure timer for LED updates
    //
    appTimerConfig(PER_LED_UPDATE_RATE);

    //
    // Start RX
    //
    basicRfReceiveOn();

    //
    // Main loop
    //
    while(1)
    {
        while(!basicRfPacketIsReady())
        {
#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
            //
            // User abort
            //
            if(bspKeyPushed(BSP_KEY_DIR_ALL) & BSP_KEY_LEFT)
            {
                appActiveModeCleanup();
                return 0;                   // Return success
            }
#endif
        }

        if(basicRfReceive((unsigned char*)&tRxPacket, MAX_PAYLOAD_LENGTH, &ssRssi) > 0)
        {
            //
	        // Change byte order from network to host order
            //
	        UINT32_NTOH(tRxPacket.seqNumber);

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
            //
            // Subtract old RSSI value from sum
            //
            tRxStats.rssiSum -= pssRssiBuf[ucRssiBufCounter];

            //
            // Store new RSSI value in ring buffer, will add it to sum later
            //
            pssRssiBuf[ucRssiBufCounter] =  ssRssi;

            //
            // Add new RSSI value to sum
            //
            tRxStats.rssiSum += ssRssi;
            if(++ucRssiBufCounter == RSSI_AVG_WINDOW_SIZE) {
                ucRssiBufCounter = 0; // Wrap counter
            }
            ssMovingAvgRssi = tRxStats.rssiSum/RSSI_AVG_WINDOW_SIZE;
#endif

            //
            // Check if the received sequence number as expected
            //
            if (tRxStats.expectedSeqNum == tRxPacket.seqNumber) {
                tRxStats.expectedSeqNum++;
            }
            //
            // If there is a jump in the sequence numbering this means some
            // packets in between have been lost.
            //
            else if (tRxStats.expectedSeqNum < tRxPacket.seqNumber){
                tRxStats.lostPkts += tRxPacket.seqNumber - tRxStats.expectedSeqNum;
                tRxStats.expectedSeqNum = tRxPacket.seqNumber + 1;
            }
            //
            // If the sequence number is lower than the previous one, assume
            // a new data burst has started and reset statistic variables.
            //
            else {
                //
                // Update our expectations assuming this is a new burst
                //
                tRxStats.expectedSeqNum = tRxPacket.seqNumber + 1;
                tRxStats.rcvdPkts = 0;
                tRxStats.lostPkts = 0;
            }

            //
            // Update received counter
            //
            tRxStats.rcvdPkts++;

            //
            // Reset statistics if select key is pressed
            //
            if(bspKeyPushed(BSP_KEY_SELECT) & BSP_KEY_SELECT)
            {
                tRxStats.rcvdPkts = 1;
                tRxStats.lostPkts = 0;
            }

            //
            // Calculate statistics
            //
            fPacketErrorRate = (float)((100*(tRxStats.lostPkts))/(float)(tRxStats.rcvdPkts + tRxStats.lostPkts));

            //
            // Update LED
            //
            ucLedPer = (unsigned char) fPacketErrorRate; // Global variable for LED updates
            perConfig.state = PER_PACKET_RECEIVED;

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
            //
            // Update LCD
            //
            lcdBufferClearPart(0, 92,127, eLcdPage2, eLcdPage5);      // Clear
            lcdBufferPrintFloat(0, fPacketErrorRate, 2, 92, eLcdPage2);// PER
            lcdBufferPrintInt(0, tRxStats.rcvdPkts, 92, eLcdPage3);    // Received
            lcdBufferPrintInt(0, tRxStats.lostPkts, 92, eLcdPage4);    // Lost
            lcdBufferPrintInt(0, ssMovingAvgRssi, 92, eLcdPage5);      // Avg. RSSI
            lcdSendBufferPart(0, 92,127, eLcdPage2,eLcdPage5);        // Send!
#endif
        }
    }
}


/******************************************************************************
* LOCAL FUNCTIONS
*/
/**************************************************************************//**
* @brief    Timer ISR.
*
* @return   None
******************************************************************************/
static void appTimerIsr(void)
{
    static unsigned char ucLedTimeout = (PER_LED_UPDATE_RATE/2);

    if(perConfig.mode == PER_MODE_RX) {
        if(perConfig.state == PER_PACKET_RECEIVED) {
            perConfig.state = PER_NO_PACKET_RECEIVED;
            ucLedTimeout = 0;
        }
        else if(ucLedTimeout == (PER_LED_UPDATE_RATE/2)) {
            appLedReset();
            return;
        }

        //
        // Increment timeout counter
        //
        ucLedTimeout++;

        //
        // Update LEDs
        //
        appLedUpdate();
    }
    else {
        //
        // TX
        //
        perConfig.state = PER_TRANSMIT;
    }
}


/**************************************************************************//**
* @brief    Configure the timer.
*
* @return   None
******************************************************************************/
static void appTimerConfig(unsigned long ulIsrPerSecond)
{
    //IntPrioritySet(INT_SMTIM, 0x80);        // Reduce timer interrupt priority
    halTimer32kInit(32768/ulIsrPerSecond);
    halTimer32kIntConnect(&appTimerIsr);    // Connect ISR
    halTimer32kIntEnable();                 // Enable interrupts
}


#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
/**************************************************************************//**
* @brief    Function writes the splash screen to the DOGM128-6 LCD display.
*
* @return   None
******************************************************************************/
static void appWriteLcdSplash(void)
{
    lcdSendBuffer(pLcdTiLogo);
    lcdBufferPrintString(0,"  CC2538",60,eLcdPage6);
    lcdBufferPrintString(0," PER TEST",60,eLcdPage7);
    lcdSendBufferPart(0, 60,127, eLcdPage6, eLcdPage7);
}


/**************************************************************************//**
* @brief    Function writes the TX mode static content to the DOGM128-6 LCD
*           display.
*
* @return   None
******************************************************************************/
static void appWriteLcdTxStatics(void)
{
    lcdBufferClear(0);

    //
    // Write static statistics text
    //
    lcdBufferPrintString(0, "Channel      : ", 2, eLcdPage1);
    lcdBufferPrintInt(0, perConfig.channel, 92, eLcdPage1);
    lcdBufferPrintString(0, "Sent pkts.   : 0", 2, eLcdPage2);
    lcdBufferPrintString(0, "Progress[%]  : 0", 2, eLcdPage3);

    //
    // Write instructions and invert
    //
    lcdBufferPrintString(0, "1 Use SELECT to", 2, eLcdPage6);
    lcdBufferPrintString(0, "  start/stop TX", 2, eLcdPage7);
    lcdBufferInvert(0, 0, 47, 127, 63);

    //
    // Write header (mimic menu)
    //
    lcdBufferPrintString(0, "PER Test", 40, eLcdPage0);
    lcdBufferPrintString(0, "1/1", 109, eLcdPage0);
    lcdBufferSetHLine(0, 0,127, 7);

    //
    // Send buffer to LCD
    //
    lcdSendBuffer(0);
}


/**************************************************************************//**
* @brief    Function writes the RX mode static content to the DOGM128-6 LCD
*           display.
*
* @return   None
******************************************************************************/
static void appWriteLcdRxStatics(void)
{
    lcdBufferClear(0);

    //
    // Write static statistics text
    //
    lcdBufferPrintString(0, "Channel      : ", 2, eLcdPage1);
    lcdBufferPrintInt(0, perConfig.channel, 92, eLcdPage1);
    lcdBufferPrintString(0, "PER[%]       : 0", 2, eLcdPage2);
    lcdBufferPrintString(0, "Good pkts.   : 0", 2, eLcdPage3);
    lcdBufferPrintString(0, "Lost pkts.   : 0", 2, eLcdPage4);
    lcdBufferPrintString(0, "Avg. RSSI    : ", 2, eLcdPage5);

    //
    // Write instructions and invert
    //
    lcdBufferPrintString(0, "1 SELECT to reset", 2, eLcdPage7);
    lcdBufferInvert(0, 0, 55, 127, 63);

    //
    // Write header (mimic menu)
    //
    lcdBufferPrintString(0, "PER Test", 40, eLcdPage0);
    lcdBufferPrintString(0, "1/1", 109, eLcdPage0);
    lcdBufferSetHLine(0, 0,127, 7);

    //
    // Send buffer to LCD
    //
    lcdSendBuffer(0);
}
#endif


/**************************************************************************//**
* @brief    Function performs cleanup after PER test active modes (RX / TX).
*
* @return   None
******************************************************************************/
static void appActiveModeCleanup(void)
{
    //
    // Disable timer interrupts
    //
    halTimer32kIntDisable();

    //
    // Turn off radio and LEDs
    //
    basicRfReceiveOff();        // Turn off radio
    bspLedClear(BSP_LED_ALL);   // Turn off LEDs

    //
    // Disable PA control signals
    //
    if(perConfig.gainMode != PER_GAIN_MODE_NONE)
    {
        HWREG(CCTEST_OBSSEL2) = 0x00;
        HWREG(CCTEST_OBSSEL3) = 0x00;
    }

    //
    // Clear untreated key presses
    //
    bspKeyPushed(BSP_KEY_ALL);

#if (defined(BOARD_SMARTRF06EB) || defined(SMARTRF06EB))
    //
    // Clear LCD buffer
    //
    lcdBufferClear(0);
#endif

}


/**************************************************************************//**
* @brief    Update LEDs according to given PER. This function does nothing if
*           the CC2538/CC2592EM is selected.
*
* @return   None
******************************************************************************/
static void appLedUpdate(void)
{
    static unsigned char ucLastPer = 0;

    //
    // Only indicate PER for standard CC2538EMs
    //
    if(perConfig.gainMode == PER_GAIN_MODE_NONE)
    {
        //
        // New range => restart sequence
        //
        if(ucLastPer != ucLedPer) {
            appLedReset();
        }

        if(ucLedPer == 0) {
            //
            // PER < 1 % (Loop 4 leds)
            //
            if (ucLedBm > 3) ucLedBm=0;
        }
        else if(ucLedPer < 5) {
            //
            // PER [1,5> % (Loop 3 leds)
            //
            if(ucLedBm > 2) ucLedBm = 0;
        }
        else if(ucLedPer < 10) {
            //
            // PER [5,10> % (Loop 2 leds)
            //
            if(ucLedBm > 1) ucLedBm = 0;
        }
        else {
            //
            // PER >= 10 % (Loop 1 led)
            //
            ucLedBm = 0;
        }
        bspLedToggle(1 << ucLedBm);
        ucLedBm++;
        ucLastPer = ucLedPer;
    }
    else
    {
        //
        // CC2538/CC2592: Only LED1 and LED2 available to CC2538
        //
        bspLedToggle(BSP_LED_1 | BSP_LED_2);
    }
}

/**************************************************************************//**
* @brief    Clear LEDs and reset bitmask counter.
*
* @return   None
******************************************************************************/
static void appLedReset(void)
{
    ucLedBm = 0;
    unsigned char ucClrBm = BSP_LED_ALL;
    if(perConfig.gainMode != PER_GAIN_MODE_NONE)
    {
        ucClrBm = (BSP_LED_1 | BSP_LED_2);
    }
    bspLedClear(ucClrBm);
}


#if (defined(BOARD_SMARTRF06BB) || defined(SMARTRF06BB))
/**************************************************************************//**
* @brief    Blink all LEDs.
*
* @return   None
******************************************************************************/
static void appLedBlink(void)
{
    volatile unsigned long ulLoop;
    bspLedSet(BSP_LED_1 | BSP_LED_2);
    for(ulLoop=0; ulLoop < 300000; ulLoop++)
    {
    }
    bspLedClear(BSP_LED_1 | BSP_LED_2);
}
#endif


/**************************************************************************//**
* Close the Doxygen group.
* @}
******************************************************************************/
