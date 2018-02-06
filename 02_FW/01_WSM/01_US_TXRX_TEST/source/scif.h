/** \mainpage Driver Overview
  *
  * \section section_drv_info Driver Information
  * This Sensor Controller Interface driver has been generated by the Texas Instruments Sensor Controller
  * Studio tool:
  * - <b>Project name</b>:     ADC Data Logger for SmartRF06EB
  * - <b>Project file</b>:     C:/Users/myeom/Documents/Texas Instruments/Sensor Controller Studio/examples/adc_data_logger/adc_data_logger.scp
  * - <b>Code prefix</b>:      -
  * - <b>Operating system</b>: TI-RTOS
  * - <b>Tool version</b>:     1.3.0.42428
  * - <b>Tool patches</b>:     None
  * - <b>Target chip</b>:      CC2630, revision -, package QFN48 7x7 RGZ
  * - <b>Created</b>:          2016-11-16 08:44:03.065
  * - <b>Computer</b>:         DESKTOP-IGSHARE
  * - <b>User</b>:             myeom
  *
  * No user-provided resource definitions were used to generate this driver.
  *
  * No user-provided procedure definitions were used to generate this driver.
  *
  * Do not edit the generated source code files other than temporarily for debug purposes. Any
  * modifications will be overwritten by the Sensor Controller Studio when generating new output.
  *
  * \section section_drv_modules Driver Modules
  * The driver is divided into three modules:
  * - \ref module_scif_generic_interface, providing the API for:
  *     - Initializing and uninitializing the driver
  *     - Task control (for starting, stopping and executing Sensor Controller tasks)
  *     - Task data exchange (for producing input data to and consume output data from Sensor Controller
  *       tasks)
  * - \ref module_scif_driver_setup, containing:
  *     - The AUX RAM image (i.e. Sensor Controller code and data)
  *     - I/O mapping information
  *     - Task data structure information
  *     - Driver setup data, to be used in the driver initialization
  *     - Project-specific functionality
  * - \ref module_scif_osal, for flexible OS support:
  *     - Interfaces with the selected operating system
  *
  * It is possible to use output from multiple Sensor Controller Studio projects in one application. Only
  * one driver setup may be active at a time, but it is possible to switch between these setups. When
  * using this option, there is one instance of the \ref module_scif_generic_interface and
  * \ref module_scif_osal modules, and multiple instances of the \ref module_scif_driver_setup module.
  * This requires that:
  * - The outputs must be generated using the same version of Sensor Controller Studio
  * - The outputs must use the same operating system
  * - The outputs must use different source code prefixes (inserted into all globals of the
  *   \ref module_scif_driver_setup)
  *
  *
  * \section section_project_info Project Description
  * Demonstrates periodical ADC sampling with storage in a circular buffer.
  * The ADC input is by default connected to the SmartRF06EB light sensor. Note that the light sensor
  * must be powered separately through ALS_PWR to be operational.
  * 
  * The Sensor Controller does not notify the System CPU application about the state of the sample
  * buffer. Instead, the System CPU wakes up periodically at a very low rate, and fetches the new samples
  * from the circular buffer.
  * The System CPU application transfers the ADC data + basic statistical information over UART, so that
  * the data can be logged and processed on the PC.
  * 
  * See the header in the application source file ("main.c" or similar) for further details and
  * instructions. This file is located in the source code output directory.
  *
  *
  * \subsection section_io_mapping I/O Mapping
  * Task I/O functions are mapped to the following pins:
  * - ADC Data Logger:
  *     - <b>A: Analog sensor output</b>: DIO29
  *
  *
  * \section section_task_info Task Description(s)
  * This driver supports the following task(s):
  *
  *
  * \subsection section_task_desc_adc_data_logger ADC Data Logger
  * Samples a single ADC channel at low rate and stores the values in a circular buffer without notifying
  * the System CPU application.
  * 
  * The System CPU application must wake up periodically, compare the new value of output.head against
  * the previous, and then fetch the latest samples from output.pSamples[].
  *
  */




/** \addtogroup module_scif_driver_setup Driver Setup
  *
  * \section section_driver_setup_overview Overview
  *
  * This driver setup instance has been generated for:
  * - <b>Project name</b>:     ADC Data Logger for SmartRF06EB
  * - <b>Code prefix</b>:      -
  *
  * The driver setup module contains the generated output from the Sensor Controller Studio project:
  * - Location of task control and scheduling data structures in AUX RAM
  * - The AUX RAM image, and the size the image
  * - Task data structure information (location, size and buffer count)
  * - I/O pin mapping translation table
  * - Task resource initialization and uninitialization functions
  *
  * @{
  */
#ifndef SCIF_H
#define SCIF_H

#include <stdint.h>
#include <stdbool.h>
#include "scif_framework.h"
#include "scif_osal_tirtos.h"


/// Target chip name
#define SCIF_TARGET_CHIP_NAME_CC2630
/// Target chip package
#define SCIF_TARGET_CHIP_PACKAGE_QFN48_7X7_RGZ

/// Number of tasks implemented by this driver
#define SCIF_TASK_COUNT 1

/// ADC Data Logger: Task ID
#define SCIF_ADC_DATA_LOGGER_TASK_ID 0


/// ADC Data Logger: ADC sample buffer size
#define SCIF_ADC_DATA_LOGGER_BUFFER_SIZE 256
/// ADC Data Logger I/O mapping: Analog sensor output
#define SCIF_ADC_DATA_LOGGER_DIO_A_SENSOR_OUTPUT 29


// All shared data structures in AUX RAM need to be packed
#pragma pack(push, 2)


/// ADC Data Logger: Task output data structure
typedef struct {
    uint16_t head;          ///< ADC sample buffer (input) head index
    uint16_t pSamples[256]; ///< ADC sample buffer
} SCIF_ADC_DATA_LOGGER_OUTPUT_T;


/// Sensor Controller task data (configuration, input buffer(s), output buffer(s) and internal state)
typedef struct {
    struct {
        SCIF_ADC_DATA_LOGGER_OUTPUT_T output;
    } adcDataLogger;
} SCIF_TASK_DATA_T;

/// Sensor Controller task generic control (located in AUX RAM)
#define scifTaskData    (*((volatile SCIF_TASK_DATA_T*) 0x400E00E6))


// Initialized internal driver data, to be used in the call to \ref scifInit()
extern const SCIF_DATA_T scifDriverSetup;


// Restore previous struct packing setting
#pragma pack(pop)


// AUX I/O re-initialization functions
void scifReinitTaskIo(uint32_t bvTaskIds);


// RTC-based tick generation control
void scifStartRtcTicks(uint32_t tickStart, uint32_t tickPeriod);
void scifStartRtcTicksNow(uint32_t tickPeriod);
void scifStopRtcTicks(void);


#endif
//@}


// Generated by DESKTOP-IGSHARE at 2016-11-16 08:44:03.065
