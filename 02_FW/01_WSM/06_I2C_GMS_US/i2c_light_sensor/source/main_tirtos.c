//*****************************************************************************
//  SENSOR CONTROLLER STUDIO EXAMPLE: I2C LIGHT SENSOR
//  Operating system: TI-RTOS
//
//  Demonstrates use of the bit-banged I2C master interface by sampling the
//  OPT3001 light sensor on the CC2650 SensorTag.
//
//  The application is woken if the light sensor output value changes by more
//  than a configurable amount:
//  - If decreasing, the application blinks the red LED1 on the SensorTag.
//  - If increasing, the application blinks the green LED2 on the SensorTag.
//
//
//  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
#include "ex_include_tirtos.h"
#include "scif.h"
#include "string.h"
#include "stdio.h"


#define BV(n)               (1 << (n))


// Display error message if the SCIF driver has been generated with incorrect operating system setting
#ifndef SCIF_OSAL_TIRTOS_H
    #error "SCIF driver has incorrect operating system configuration for this example. Please change to 'TI-RTOS' in the Sensor Controller Studio project panel and re-generate the driver."
#endif

// Display error message if the SCIF driver has been generated with incorrect target chip package
#ifndef SCIF_TARGET_CHIP_PACKAGE_QFN48_7X7_RGZ
    #error "SCIF driver has incorrect target chip package configuration for this example. Please change to 'QFN48 7x7 RGZ' in the Sensor Controller Studio project panel and re-generate the driver."
#endif

// UART driver objects
UART_Handle uHandle;
UART_Params uParams;

// Line buffer for UART printing
char pLine[32];


// Task data
Task_Struct myTask;
Char myTaskStack[1024];


// Semaphore used to wait for Sensor Controller task ALERT event
static Semaphore_Struct semScTaskAlert;




void scCtrlReadyCallback(void) {

} // scCtrlReadyCallback




void scTaskAlertCallback(void) {

    // Wake up the OS task
    Semaphore_post(Semaphore_handle(&semScTaskAlert));

} // scTaskAlertCallback




PIN_Config pLedPinTable[] = {
    Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    Board_LED2 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};
PIN_State ledPinState;


void taskFxn(UArg a0, UArg a1) {
    PIN_Handle hLedPins;

    // Enable LED pins
    hLedPins = PIN_open(&ledPinState, pLedPinTable);
    PIN_setOutputValue(hLedPins, Board_LED1, 1);
    // Initialize UART parameters
    UART_Params_init(&uParams);
    uParams.baudRate      = 57600;
    uParams.writeDataMode = UART_DATA_TEXT;
    uParams.dataLength    = UART_LEN_8;
    uParams.stopBits      = UART_STOP_ONE;
    
    
    // Initialize the Sensor Controller
    scifOsalInit();
    scifOsalRegisterCtrlReadyCallback(scCtrlReadyCallback);
    scifOsalRegisterTaskAlertCallback(scTaskAlertCallback);
    scifInit(&scifDriverSetup);

    // Set the Sensor Controller task tick interval to 1 second
    //scifStartRtcTicksNow(0x00010000);
    scifStartRtcTicksNow(0x00010000);

    // Configure to trigger interrupt at first result, and start the Sensor Controller's I2C Light
    // Sensor task (not to be confused with OS tasks)
    int isInitialSetting  = scifTaskData.i2cLightSensor.cfg.isInitialSetting;
    int16_t initX[16]={0,};
    int16_t initY[16]={0,};
    int16_t initZ[16]={0,};
    
    static int initGetCnt = 0;
    int xAvg = 0;
    int yAvg = 0;
    int zAvg = 0;
//    int highThreshold = scifTaskData.i2cLightSensor.cfg.highThreshold = 0;
    scifStartTasksNbl(BV(SCIF_I2C_LIGHT_SENSOR_TASK_ID));

    // Main loop
    while (1) {

        // Wait for an ALERT callback
        Semaphore_pend(Semaphore_handle(&semScTaskAlert), BIOS_WAIT_FOREVER);
        
        
        // Open UART
        uHandle = UART_open(Board_UART, &uParams);

        // Clear the ALERT interrupt source
        scifClearAlertIntSource();

        // The light sensor value is outside of the configured window ...
        int16_t valueXH = scifTaskData.i2cLightSensor.output.xHigh;
        int16_t valueXL = scifTaskData.i2cLightSensor.output.xLow;
        int16_t valueYH = scifTaskData.i2cLightSensor.output.yHigh;
        int16_t valueYL = scifTaskData.i2cLightSensor.output.yLow;
        int16_t valueZH = scifTaskData.i2cLightSensor.output.zHigh;
        int16_t valueZL = scifTaskData.i2cLightSensor.output.zLow;
        
        int16_t valueX = (valueXH<<8) | valueXL;
        int16_t valueY = (valueYH<<8) | valueYL;
        int16_t valueZ = (valueZH<<8) | valueZL;
        
        int isInitialSetting  = scifTaskData.i2cLightSensor.cfg.isInitialSetting;
        if(isInitialSetting == 0){
          initX[initGetCnt] = valueX;
          initY[initGetCnt] = valueY;
          initZ[initGetCnt] = valueZ;
          initGetCnt++;
          int sign = 1;
          if(initGetCnt == 16)
          {
            for(int i=0; i<16; i++)
            {
              xAvg += initX[i];
              yAvg += initY[i];
              zAvg += initZ[i];
            }
            
            if(xAvg<0)
            {
              xAvg = -1*xAvg;
              sign = -1;
            }
            xAvg = xAvg>>4;
            xAvg = xAvg*sign;
            sign = 1;
            
            if(yAvg<0)
            {
              yAvg = -1*yAvg;
              sign = -1;
            }
            yAvg = yAvg>>4;
            yAvg = yAvg*sign;
            sign = 1;
            
            if(zAvg<0)
            {
              zAvg = -1*zAvg;
              sign = -1;
            }
            zAvg = zAvg>>4;
            zAvg = zAvg*sign;

            
            scifTaskData.i2cLightSensor.output.initXVal = xAvg;
            scifTaskData.i2cLightSensor.output.initYVal = yAvg;
            scifTaskData.i2cLightSensor.output.initZVal = zAvg;
            scifTaskData.i2cLightSensor.cfg.isInitialSetting = 1;
            
            sprintf(pLine, "IGS%0.6d%0.6d%0.6digs\r\n", 0, 0, 1);
            UART_write(uHandle, pLine, strlen(pLine));
            sprintf(pLine, "IGS%0.6d%0.6d%0.6digs\r\n", xAvg, yAvg, zAvg);
            UART_write(uHandle, pLine, strlen(pLine));
          
          } else{
            sprintf(pLine, "IGS%0.6d%0.6d%0.6digs\r\n", valueX, valueY, valueZ);
            UART_write(uHandle, pLine, strlen(pLine));
        }
        }else{
          //sprintf(pLine, "IGS%0.6d%0.6d%0.6digs\r\n", valueX, valueY, valueZ);
          //UART_write(uHandle, pLine, strlen(pLine));
         // Fetch the current head index
          uint16_t head = scifTaskData.i2cLightSensor.output.head;
          uint16_t tail = scifTaskData.i2cLightSensor.output.tail;

          // Initialize statistics to be outputted after each chunk of ADC values
          uint16_t count = (head - tail + SCIF_I2C_LIGHT_SENSOR_BUFFER_SIZE) % SCIF_I2C_LIGHT_SENSOR_BUFFER_SIZE;

          // Until we've caught up with the Sensor Controller ...
          
          sprintf(pLine, "IGS");
          UART_write(uHandle, pLine, strlen(pLine));
          
          while (tail != head) {

              // Output the ADC value over UART
              uint16_t value = scifTaskData.i2cLightSensor.output.pSamples[tail];
              sprintf(pLine, "%0.6d", value);
              UART_write(uHandle, pLine, strlen(pLine));

              // Increment the tail index
              if (++tail >= SCIF_I2C_LIGHT_SENSOR_BUFFER_SIZE) {
                  tail = 0;
              }
          }
          
           sprintf(pLine, "igs");
           UART_write(uHandle, pLine, strlen(pLine));
           scifTaskData.i2cLightSensor.output.tail = tail;
          }

      
        //sprintf(pLine, "IGS%0.6d%0.6d%0.6digs\r\n", valueX, valueY, valueZ);
        //UART_write(uHandle, pLine, strlen(pLine));

        // Close UART
        UART_close(uHandle);
        
       

        // Acknowledge the alert event
        scifAckAlertEvents();
    }

} // taskFxn




int main(void) {
    Task_Params taskParams;

    // Initialize the PIN driver
    PIN_init(BoardGpioInitTable);

    // Configure the OS task
    Task_Params_init(&taskParams);
    taskParams.stack = myTaskStack;
    taskParams.stackSize = sizeof(myTaskStack);
    taskParams.priority = 3;
    Task_construct(&myTask, taskFxn, &taskParams, NULL);

    // Create the semaphore used to wait for Sensor Controller ALERT events
    Semaphore_Params semParams;
    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&semScTaskAlert, 0, &semParams);

    // Start TI-RTOS
    BIOS_start();
    return 0;

} // main
