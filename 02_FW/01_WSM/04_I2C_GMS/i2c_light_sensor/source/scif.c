/// \addtogroup module_scif_driver_setup
//@{
#include "scif.h"
#include "scif_framework.h"
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <inc/hw_aon_event.h>
#include <inc/hw_aon_rtc.h>
#include <inc/hw_aon_wuc.h>
#include <inc/hw_aux_sce.h>
#include <inc/hw_aux_smph.h>
#include <inc/hw_aux_evctl.h>
#include <inc/hw_aux_aiodio.h>
#include <inc/hw_aux_timer.h>
#include <inc/hw_aux_wuc.h>
#include <inc/hw_event.h>
#include <inc/hw_ints.h>
#include <inc/hw_ioc.h>
#include <string.h>
#if defined(__IAR_SYSTEMS_ICC__)
    #include <intrinsics.h>
#endif


// OSAL function prototypes
uint32_t scifOsalEnterCriticalSection(void);
void scifOsalLeaveCriticalSection(uint32_t key);




/// Firmware image to be uploaded to the AUX RAM
static const uint16_t pAuxRamImage[] = {
    /*0x0000*/ 0x1408, 0x040C, 0x1408, 0x042C, 0x1408, 0x0447, 0x1408, 0x044D, 0x4436, 0x2437, 0xAEFE, 0xADB7, 0x6442, 0x7000, 0x7C6B, 0x6870, 
    /*0x0020*/ 0x0068, 0x1425, 0x6871, 0x0069, 0x1425, 0x6872, 0x006A, 0x1425, 0x786B, 0xF801, 0xFA01, 0xBEF2, 0x786E, 0x6870, 0xFD0E, 0x6872, 
    /*0x0040*/ 0xED92, 0xFD06, 0x7C6E, 0x642D, 0x0451, 0x786B, 0x8F1F, 0xED8F, 0xEC01, 0xBE01, 0xADB7, 0x8DB7, 0x6630, 0x6542, 0x0000, 0x186E, 
    /*0x0060*/ 0x9D88, 0x9C01, 0xB60D, 0x1067, 0xAF19, 0xAA00, 0xB609, 0xA8FF, 0xAF39, 0xBE06, 0x0C6B, 0x8869, 0x8F08, 0xFD47, 0x9DB7, 0x086B, 
    /*0x0080*/ 0x8801, 0x8A01, 0xBEEC, 0x262F, 0xAEFE, 0x4630, 0x0451, 0x5527, 0x6642, 0x0000, 0x0C6B, 0x1501, 0x0451, 0x6742, 0x86FF, 0x03FF, 
    /*0x00A0*/ 0x0C6D, 0x786C, 0xCD47, 0x686D, 0xCD06, 0xB605, 0x0000, 0x0C6C, 0x7C6F, 0x652D, 0x0C6D, 0x786D, 0xF801, 0xE92B, 0xFD0E, 0xBE01, 
    /*0x00C0*/ 0x6436, 0xBDB7, 0x241A, 0xA6FE, 0xADB7, 0x641A, 0xADB7, 0x0000, 0x007E, 0x00ED, 0x0167, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
    /*0x00E0*/ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6000, 
    /*0x0100*/ 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x700F, 0x687D, 0x1588, 0x6C7D, 0x587D, 0xDA00, 0xBE0C, 0x687D, 0x156A, 0x6C7D, 
    /*0x0120*/ 0x7039, 0x687D, 0x1588, 0x6C7D, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0x8D47, 0x687D, 0x15C3, 0x6C7D, 0x8A3D, 0xBE4C, 0x750E, 0x7093, 
    /*0x0140*/ 0x600E, 0x15CE, 0x6000, 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x7020, 0x687D, 0x1588, 0x6C7D, 0x7000, 0x687D, 0x1588, 
    /*0x0160*/ 0x6C7D, 0x687D, 0x15C3, 0x6C7D, 0x6000, 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x7021, 0x687D, 0x1588, 0x6C7D, 0x7000, 
    /*0x0180*/ 0x687D, 0x1588, 0x6C7D, 0x687D, 0x15C3, 0x6C7D, 0x6000, 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x7022, 0x687D, 0x1588, 
    /*0x01A0*/ 0x6C7D, 0x7020, 0x687D, 0x1588, 0x6C7D, 0x687D, 0x15C3, 0x6C7D, 0x6000, 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x7023, 
    /*0x01C0*/ 0x687D, 0x1588, 0x6C7D, 0x7000, 0x687D, 0x1588, 0x6C7D, 0x687D, 0x15C3, 0x6C7D, 0x0001, 0x0C67, 0xADB7, 0x0873, 0x8A01, 0xBE04, 
    /*0x01E0*/ 0x750E, 0x700F, 0x600E, 0x15CE, 0x550E, 0x470E, 0x0078, 0x8B0D, 0x8608, 0x7022, 0xFB0A, 0x7025, 0x15D4, 0x6444, 0x0001, 0x0C67, 
    /*0x0200*/ 0xADB7, 0x6000, 0x1570, 0x6C7D, 0x7038, 0x687D, 0x1588, 0x6C7D, 0x7027, 0x687D, 0x1588, 0x6C7D, 0x087D, 0x8A00, 0xBE54, 0x687D, 
    /*0x0220*/ 0x156A, 0x6C7D, 0x7039, 0x687D, 0x1588, 0x6C7D, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0xF004, 0xFA04, 0xBE46, 0x7000, 0x687D, 0x15A5, 
    /*0x0240*/ 0x6C7D, 0x7C78, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0x7C77, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0x7C7A, 0x7000, 0x687D, 0x15A5, 0x6C7D, 
    /*0x0260*/ 0x7C79, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0x7C7C, 0x7000, 0x687D, 0x15A5, 0x6C7D, 0x7C7B, 0x0873, 0x8A01, 0xBE22, 0x0877, 0x8DA0, 
    /*0x0280*/ 0x1878, 0x8D09, 0x1879, 0x9DA0, 0x287A, 0x9D0A, 0x287B, 0xADA0, 0x387C, 0xAD0B, 0x3874, 0xBD18, 0x0875, 0x8D19, 0x1876, 0x9D1A, 
    /*0x02A0*/ 0xBA00, 0xE601, 0xBD91, 0x8A00, 0xE601, 0x8D91, 0x9A00, 0xE601, 0x9D91, 0xAD43, 0xAD20, 0xAD21, 0x8603, 0xAAE8, 0xFE01, 0x670E, 
    /*0x02C0*/ 0x086C, 0x8201, 0x0C6C, 0x687D, 0x15C3, 0x6C7D, 0xADB7, 0x5527, 0x6642, 0xADB7, 0x5035, 0x1575, 0x650F, 0x157A, 0x5031, 0x1575, 
    /*0x02E0*/ 0x440F, 0x502C, 0x1575, 0x450F, 0xADB7, 0xDD91, 0xDDB9, 0xD801, 0xBEFE, 0xADB7, 0x7741, 0x5030, 0xDB09, 0x504B, 0xDB0C, 0x640B, 
    /*0x0300*/ 0x2513, 0xAE04, 0x8650, 0x370C, 0xA6FB, 0xE202, 0x440B, 0xADB7, 0xEA00, 0xBE1A, 0xB50D, 0xFDA1, 0x8601, 0xFC00, 0xB602, 0x640F, 
    /*0x0320*/ 0x8E01, 0x440F, 0x5035, 0x1575, 0x650F, 0x157A, 0x5029, 0x1575, 0x450F, 0x640F, 0x5035, 0x1575, 0x650F, 0x157A, 0x5029, 0x1575, 
    /*0x0340*/ 0x2413, 0xA601, 0xE201, 0x450F, 0xADB7, 0xEA00, 0xBE1B, 0xB50B, 0x640F, 0x5035, 0x1575, 0x650F, 0x157A, 0x5029, 0x1575, 0xFDA1, 
    /*0x0360*/ 0x2413, 0xA601, 0xF201, 0x450F, 0x8601, 0xFC00, 0xB602, 0x640F, 0x8E01, 0x440F, 0x5035, 0x1575, 0x650F, 0x157A, 0x5029, 0x1575, 
    /*0x0380*/ 0x450F, 0xF0FF, 0xADB7, 0x440F, 0x5035, 0x1575, 0x650F, 0x157A, 0x5029, 0x1575, 0x640F, 0x5033, 0x1575, 0xADB7, 0xFB0C, 0xEDA4, 
    /*0x03A0*/ 0xEB09, 0x640B, 0xCDB1, 0xADB7, 0x5527, 0x6642, 0x862B, 0xF200, 0xFB27, 0xADB7
};


/// Look-up table that converts from AUX I/O index to MCU IOCFG offset
static const uint8_t pAuxIoIndexToMcuIocfgOffsetLut[] = {
    120, 116, 112, 108, 104, 100, 96, 92, 28, 24, 20, 16, 12, 8, 4, 0
};


/** \brief Look-up table of data structure information for each task
  *
  * There is one entry per data structure (\c cfg, \c input, \c output and \c state) per task:
  * - [31:20] Data structure size (number of 16-bit words)
  * - [19:12] Buffer count (when 2+, first data structure is preceded by buffering control variables)
  * - [11:0] Address of the first data structure
  */
static const uint32_t pScifTaskDataStructInfoLut[] = {
//  cfg         input       output      state       
    0x001010E6, 0x00000000, 0x009010E8, 0x001010FA  // I2C Light Sensor
};




// No task-specific initialization functions




// No task-specific uninitialization functions




/** \brief Initilializes task resource hardware dependencies
  *
  * This function is called by the internal driver initialization function, \ref scifInit().
  */
static void scifTaskResourceInit(void) {
    scifInitIo(5, AUXIOMODE_OUTPUT, -1, 0);
    scifInitIo(3, AUXIOMODE_OUTPUT, -1, 0);
    scifInitIo(9, AUXIOMODE_OPEN_DRAIN_WITH_INPUT, -1, 1);
    HWREG((IOC_BASE + IOC_O_IOCFG0) + pAuxIoIndexToMcuIocfgOffsetLut[9]) |= IOC_IOCFG0_HYST_EN_M;
    scifInitIo(8, AUXIOMODE_OPEN_DRAIN_WITH_INPUT, -1, 1);
    HWREG((IOC_BASE + IOC_O_IOCFG0) + pAuxIoIndexToMcuIocfgOffsetLut[8]) |= IOC_IOCFG0_HYST_EN_M;
    HWREG(AON_WUC_BASE + AON_WUC_O_AUXCLK) = (AON_WUC_AUXCLK_SRC_SCLK_HF | AON_WUC_AUXCLK_SCLK_HF_DIV_DIV2) | AON_WUC_AUXCLK_PWR_DWN_SRC_SCLK_LF;
    HWREG(AON_RTC_BASE + AON_RTC_O_CTL) |= AON_RTC_CTL_RTC_4KHZ_EN;
} // scifTaskResourceInit




/** \brief Uninitilializes task resource hardware dependencies
  *
  * This function is called by the internal driver uninitialization function, \ref scifUninit().
  */
static void scifTaskResourceUninit(void) {
    scifUninitIo(5, -1);
    scifUninitIo(3, -1);
    scifUninitIo(9, -1);
    scifUninitIo(8, -1);
    HWREG(AON_WUC_BASE + AON_WUC_O_AUXCLK) = (AON_WUC_AUXCLK_SRC_SCLK_HF | AON_WUC_AUXCLK_SCLK_HF_DIV_DIV2) | AON_WUC_AUXCLK_PWR_DWN_SRC_NONE;
    HWREG(AON_RTC_BASE + AON_RTC_O_CTL) &= ~AON_RTC_CTL_RTC_4KHZ_EN;
} // scifTaskResourceUninit




/** \brief Re-initializes I/O pins used by the specified tasks
  *
  * It is possible to stop a Sensor Controller task and let the System CPU borrow and operate its I/O
  * pins. For example, the Sensor Controller can operate an SPI interface in one application state while
  * the System CPU with SSI operates the SPI interface in another application state.
  *
  * This function must be called before \ref scifExecuteTasksOnceNbl() or \ref scifStartTasksNbl() if
  * I/O pins belonging to Sensor Controller tasks have been borrowed System CPU peripherals.
  *
  * \param[in]      bvTaskIds
  *     Bit-vector of task IDs for the task I/Os to be re-initialized
  */
void scifReinitTaskIo(uint32_t bvTaskIds) {
    if (bvTaskIds & (1 << SCIF_I2C_LIGHT_SENSOR_TASK_ID)) {
        scifReinitIo(5, -1);
        scifReinitIo(3, -1);
        scifReinitIo(9, -1);
        HWREG((IOC_BASE + IOC_O_IOCFG0) + pAuxIoIndexToMcuIocfgOffsetLut[9]) |= IOC_IOCFG0_HYST_EN_M;
        scifReinitIo(8, -1);
        HWREG((IOC_BASE + IOC_O_IOCFG0) + pAuxIoIndexToMcuIocfgOffsetLut[8]) |= IOC_IOCFG0_HYST_EN_M;
    }
} // scifReinitTaskIo




/// Driver setup data, to be used in the call to \ref scifInit()
const SCIF_DATA_T scifDriverSetup = {
    (volatile SCIF_INT_DATA_T*) 0x400E00D6,
    (volatile SCIF_TASK_CTRL_T*) 0x400E00DC,
    (volatile uint16_t*) 0x400E00CE,
    0x0000,
    sizeof(pAuxRamImage),
    pAuxRamImage,
    pScifTaskDataStructInfoLut,
    pAuxIoIndexToMcuIocfgOffsetLut,
    scifTaskResourceInit,
    scifTaskResourceUninit
};




/** \brief Starts or modifies RTC-based task scheduling tick generation
  *
  * RTC-based tick generation will wake up the Sensor Controller first at the specified value of the RTC
  * and then periodically at the specified interval. The application must call this function after
  * calling \ref scifInit().
  *
  * The application must ensure that:
  * - \a tickStart is not in the past (prefer using \ref scifStartRtcTicksNow() to avoid this)
  * - \a tickPeriod is not too short. RTC ticks will be skipped silently if the Sensor Controller does
  *   not complete its tasks within a single tick interval.
  *
  * \param[in]      tickStart
  *     RTC value when the first tick is generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  * \param[in]      tickPeriod
  *     Interval at which subsequent ticks are generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  */
void scifStartRtcTicks(uint32_t tickStart, uint32_t tickPeriod) {
    HWREG(AON_RTC_BASE + AON_RTC_O_CH2CMP) = tickStart;
    HWREG(AON_RTC_BASE + AON_RTC_O_CH2CMPINC) = tickPeriod;
    HWREG(AON_RTC_BASE + AON_RTC_O_CHCTL) |= AON_RTC_CHCTL_CH2_EN_M | AON_RTC_CHCTL_CH2_CONT_EN_M;
    HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) =
        (HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) & ~AON_EVENT_AUXWUSEL_WU0_EV_M) |
        (AON_EVENT_AUXWUSEL_WU0_EV_RTC_CH2);
} // scifStartRtcTicks




/** \brief Starts or modifies RTC-based task scheduling tick generation
  *
  * RTC-based tick generation will wake up the Sensor Controller first after approximately 128 us and
  * then periodically at the specified interval. The application must call this function after calling
  * \ref scifInit().
  *
  * The application must ensure that \a tickPeriod is not too short. RTC ticks will be skipped silently
  * if the Sensor Controller does not complete its tasks within a single tick interval.
  *
  * \param[in]      tickPeriod
  *     Interval at which subsequent ticks are generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  */
void scifStartRtcTicksNow(uint32_t tickPeriod) {
    uint32_t key, sec, subsec;
    key = scifOsalEnterCriticalSection();
    sec = HWREG(AON_RTC_BASE + AON_RTC_O_SEC);
    subsec = HWREG(AON_RTC_BASE + AON_RTC_O_SUBSEC);
    scifStartRtcTicks(((sec << 16) | (subsec >> 16)) + 8, tickPeriod);
    scifOsalLeaveCriticalSection(key);
} // scifStartRtcTicksNow




/** \brief Stops RTC-based task scheduling tick generation
  *
  * The application must call this function before calling \ref scifUninit().
  */
void scifStopRtcTicks(void) {
    HWREG(AON_RTC_BASE + AON_RTC_O_CHCTL) &= ~(AON_RTC_CHCTL_CH2_EN_M | AON_RTC_CHCTL_CH2_CONT_EN_M);
    HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) =
        (HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) & ~AON_EVENT_AUXWUSEL_WU0_EV_M) |
        (AON_EVENT_AUXWUSEL_WU0_EV_NONE);
    HWREG(AON_RTC_BASE + AON_RTC_O_SYNC);
} // scifStopRtcTicks


//@}


// Generated by DESKTOP-IGSHARE at 2017-02-14 14:57:48.691
