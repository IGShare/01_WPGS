/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.platforms.tiva package and will be overwritten.
 */

"E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\06_I2C_GMS_US\i2c_light_sensor\projects\iar_tirtos\configPkg\package\cfg\rom_prm3.orm3"
"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages/ti/drivers/rf/lib/rf_singleMode_cc26xxware.arm3"
"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages/ti/drivers/lib/drivers_cc26xxware.arm3"
"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages/ti/drivers/lib/power_cc26xx_tirtos.arm3"
"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages/ti/drivers/pdm/lib/pdm_cc26xxware.arm3"
"C:\ti\tirtos_cc13xx_cc26xx_2_21_00_06\products\tidrivers_cc13xx_cc26xx_2_21_00_04\packages\ti\mw\fatfs\lib\release\ti.mw.fatfs.arm3"
"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages/ti/drivers/ports/lib/tirtosport.arm3"
"E:\igs_svn_data\PROJECT_01\02_FW\01_WSM\06_I2C_GMS_US\i2c_light_sensor\projects\iar_tirtos\src\sysbios\rom_sysbios.arm3"
"C:\ti\tirtos_cc13xx_cc26xx_2_21_00_06\products\bios_6_46_01_37\packages\iar\targets\arm\rts\lib\release\boot.arm3"


/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from iar.targets.arm (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from iar.targets.arm.rts (): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from ti.sysbios.family.arm (ti/sysbios/family/arm/linkcmd.xdt): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.rom (null): */

/* Content from ti.sysbios.rts (ti/sysbios/rts/linkcmd.xdt): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.catalog.arm.cortexm3 (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.arm.peripherals.timers (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.catalog.arm.cortexm4 (null): */

/* Content from ti.platforms.simplelink (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.family.arm.cc26xx (null): */

/* Content from ti.sysbios.family.arm.m3 (ti/sysbios/family/arm/m3/linkcmd.xdt): */
--entry __iar_program_start
--keep __vector_table
--define_symbol ti_sysbios_family_arm_m3_Hwi_nvic=0xe000e000

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.drivers.ports (null): */

/* Content from ti.mw.fatfs (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sysbios.rom.cortexm.cc26xx (C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/sysbios/rom/cortexm/cc26xx/golden/CC26xx/CC26xx_link_iar.xdt): */

--keep xdc_runtime_Error_policy__C
--keep xdc_runtime_IModule_Interface__BASE__C
--keep xdc_runtime_Startup_lastFxns__C
--keep ti_sysbios_gates_GateMutex_Object__DESC__C
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_initDevice__I
--keep xdc_runtime_Startup_execImpl__C
--keep ti_sysbios_gates_GateMutex_Instance_State_sem__O
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getMaxTicks__E
--keep ti_sysbios_knl_Swi_Object__count__C
--keep ti_sysbios_knl_Idle_funcList__C
--keep ti_sysbios_family_arm_m3_Hwi_Object__PARAMS__C
--keep xdc_runtime_Text_isLoaded__C
--keep ti_sysbios_knl_Clock_Object__DESC__C
--keep ti_sysbios_knl_Mailbox_Instance_State_dataQue__O
--keep ti_sysbios_gates_GateMutex_Module__FXNS__C
--keep ti_sysbios_knl_Task_Module_State_inactiveQ__O
--keep ti_sysbios_family_arm_m3_Hwi_Module__id__C
--keep ti_sysbios_family_arm_cc26xx_Timer_Module__id__C
--keep ti_sysbios_knl_Mailbox_Object__table__C
--keep ti_sysbios_family_arm_m3_Hwi_Object__table__C
--keep ti_sysbios_knl_Swi_Object__DESC__C
--keep xdc_runtime_Text_charCnt__C
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_start__E
--keep ti_sysbios_heaps_HeapMem_Object__table__C
--keep xdc_runtime_Error_policyFxn__C
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCount64__E
--keep xdc_runtime_Startup_firstFxns__C
--keep ti_sysbios_knl_Swi_Object__PARAMS__C
--keep ti_sysbios_knl_Clock_serviceMargin__C
--keep xdc_runtime_Text_charTab__C
--keep ti_sysbios_rom_ROM_AONRTCCurrentCompareValueGet
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_TimestampProvider_get32__E
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_getCurrentTick__E
--keep ti_sysbios_family_arm_m3_TaskSupport_stackAlignment__C
--keep ti_sysbios_family_arm_m3_Hwi_NUM_INTERRUPTS__C
--keep xdc_runtime_Main_Module__diagsMask__C
--keep ti_sysbios_knl_Swi_Object__table__C
--keep xdc_runtime_Memory_Module__id__C
--keep ti_sysbios_knl_Task_Object__PARAMS__C
--keep ti_sysbios_gates_GateMutex_Object__PARAMS__C
--keep ti_sysbios_heaps_HeapMem_Module__gateObj__C
--keep ti_sysbios_family_arm_cc26xx_Timer_startupNeeded__C
--keep ti_sysbios_knl_Queue_Object__DESC__C
--keep ti_sysbios_knl_Task_Object__DESC__C
--keep xdc_runtime_Assert_E_assertFailed__C
--keep ti_sysbios_heaps_HeapMem_Object__PARAMS__C
--keep ti_sysbios_gates_GateHwi_Module__id__C
--keep ti_sysbios_gates_GateHwi_Object__PARAMS__C
--keep xdc_runtime_IHeap_Interface__BASE__C
--keep xdc_runtime_SysCallback_exitFxn__C
--keep ti_sysbios_heaps_HeapMem_Module__id__C
--keep ti_sysbios_family_arm_m3_Hwi_excHandlerFunc__C
--keep ti_sysbios_heaps_HeapMem_Module__FXNS__C
--keep xdc_runtime_System_maxAtexitHandlers__C
--keep ti_sysbios_knl_Queue_Object__count__C
--keep ti_sysbios_knl_Task_Object__table__C
--keep ti_sysbios_knl_Mailbox_Object__DESC__C
--keep ti_sysbios_family_arm_m3_Hwi_nullIsrFunc__C
--keep ti_sysbios_knl_Clock_tickMode__C
--keep ti_sysbios_gates_GateMutex_Module__id__C
--keep ti_sysbios_knl_Swi_numPriorities__C
--keep ti_sysbios_knl_Task_numConstructedTasks__C
--keep xdc_runtime_Startup_maxPasses__C
--keep ti_sysbios_rom_ROM_AONRTCEventClear
--keep ti_sysbios_knl_Task_initStackFlag__C
--keep xdc_runtime_Main_Module__diagsEnabled__C
--keep xdc_runtime_Main_Module__diagsIncluded__C
--keep xdc_runtime_System_abortFxn__C
--keep ti_sysbios_knl_Mailbox_Instance_State_dataSem__O
--keep ti_sysbios_gates_GateHwi_Module__FXNS__C
--keep ti_sysbios_hal_Hwi_Object__DESC__C
--keep ti_sysbios_family_arm_m3_Hwi_priGroup__C
--keep xdc_runtime_Error_E_memory__C
--keep ti_sysbios_family_arm_m3_Hwi_E_alreadyDefined__C
--keep ti_sysbios_knl_Mailbox_Instance_State_freeSem__O
--keep ti_sysbios_knl_Queue_Object__table__C
--keep ti_sysbios_knl_Semaphore_Object__PARAMS__C
--keep xdc_runtime_System_exitFxn__C
--keep ti_sysbios_knl_Clock_Object__PARAMS__C
--keep ti_sysbios_rom_ROM_AONRTCCompareValueSet
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setNextTick__E
--keep ti_sysbios_heaps_HeapMem_reqAlign__C
--keep xdc_runtime_Main_Module__id__C
--keep xdc_runtime_Startup_sfxnRts__C
--keep ti_sysbios_knl_Semaphore_Object__DESC__C
--keep ti_sysbios_gates_GateHwi_Object__DESC__C
--keep ti_sysbios_heaps_HeapMem_Object__count__C
--keep ti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__C
--keep ti_sysbios_family_arm_cc26xx_TimestampProvider_useClockTimer__C
--keep ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_exit__E
--keep ti_sysbios_knl_Queue_Object__PARAMS__C
--keep ti_sysbios_knl_Task_allBlockedFunc__C
--keep ti_sysbios_rom_ROM_xdc_runtime_System_SupportProxy_abort__E
--keep ti_sysbios_knl_Mailbox_Object__count__C
--keep xdc_runtime_Text_nameStatic__C
--keep ti_sysbios_rom_ROM_xdc_runtime_Startup_getState__I
--keep ti_sysbios_knl_Clock_Module_State_clockQ__O
--keep ti_sysbios_knl_Task_defaultStackSize__C
--keep xdc_runtime_IGateProvider_Interface__BASE__C
--keep ti_sysbios_family_arm_m3_Hwi_E_hwiLimitExceeded__C
--keep xdc_runtime_Startup_startModsFxn__C
--keep ti_sysbios_knl_Semaphore_Instance_State_pendQ__O
--keep ti_sysbios_family_arm_m3_Hwi_Object__DESC__C
--keep xdc_runtime_Text_nameEmpty__C
--keep ti_sysbios_family_arm_m3_Hwi_Object__count__C
--keep xdc_runtime_SysCallback_abortFxn__C
--keep ti_sysbios_knl_Task_defaultStackHeap__C
--keep ti_sysbios_family_arm_m3_Hwi_ccr__C
--keep ti_sysbios_knl_Mailbox_Object__PARAMS__C
--keep ti_sysbios_hal_Hwi_Object__PARAMS__C
--keep ti_sysbios_heaps_HeapMem_E_memory__C
--keep ti_sysbios_knl_Task_Object__count__C
--keep ti_sysbios_rom_ROM_AONRTCChannelEnable
--keep ti_sysbios_heaps_HeapMem_Object__DESC__C
--keep xdc_runtime_Text_nameUnknown__C
--keep xdc_runtime_Memory_defaultHeapInstance__C
--keep ti_sysbios_knl_Mailbox_Instance_State_freeQue__O
--keep ti_sysbios_rom_ROM_ti_sysbios_family_arm_cc26xx_Timer_setThreshold__I
--keep xdc_runtime_Startup_sfxnTab__C
--keep ti_sysbios_knl_Clock_Module__state__V
--keep ti_sysbios_family_arm_cc26xx_TimestampProvider_Module__state__V
--keep xdc_runtime_Startup_Module__state__V
--keep ti_sysbios_BIOS_Module__state__V
--keep ti_sysbios_knl_Swi_Module__state__V
--keep ti_sysbios_knl_Task_Module__state__V
--keep xdc_runtime_Memory_Module__state__V
--keep xdc_runtime_System_Module__state__V
--keep ti_sysbios_family_arm_m3_Hwi_Module__state__V
--keep ti_sysbios_family_arm_cc26xx_Timer_Module__state__V

--define_symbol memcpy=0x1001ca79
--define_symbol memset=0x1001ca8b
--define_symbol ti_sysbios_rom_cortexm_cc26xx_CC26xx_getRevision__E=0x1001ca9b
--define_symbol ti_sysbios_knl_Queue_get__E=0x1001bf11
--define_symbol ti_sysbios_knl_Swi_enabled__E=0x1001c0e5
--define_symbol ti_sysbios_knl_Clock_scheduleNextTick__E=0x1001bebd
--define_symbol ti_sysbios_knl_Swi_runLoop__I=0x1001b0d5
--define_symbol ti_sysbios_knl_Clock_getTicks__E=0x1001b6d9
--define_symbol ti_sysbios_gates_GateMutex_Object__destruct__S=0x1001bc49
--define_symbol ti_sysbios_knl_Queue_enqueue__E=0x1001c1b5
--define_symbol ti_sysbios_knl_Queue_put__E=0x1001bf2d
--define_symbol ti_sysbios_family_arm_m3_Hwi_Object__create__S=0x1001aab1
--define_symbol ti_sysbios_gates_GateHwi_Instance_init__E=0x1001b463
--define_symbol ti_sysbios_hal_Hwi_Instance_finalize__E=0x1001c1f1
--define_symbol ti_sysbios_BIOS_RtsGateProxy_leave__E=0x1001c24d
--define_symbol ti_sysbios_heaps_HeapMem_Object__create__S=0x1001b845
--define_symbol xdc_runtime_Error_raiseX__E=0x1001c769
--define_symbol ti_sysbios_knl_Semaphore_construct=0x1001b709
--define_symbol ti_sysbios_knl_Clock_Object__destruct__S=0x1001bce9
--define_symbol ti_sysbios_knl_Clock_TimerProxy_getMaxTicks__E=0x1001c0a5
--define_symbol ti_sysbios_knl_Swi_Object__destruct__S=0x1001bf49
--define_symbol ti_sysbios_family_arm_cc26xx_TimestampProvider_getFreq__E=0x1001c12f
--define_symbol ti_sysbios_gates_GateMutex_Handle__label__S=0x1001bc29
--define_symbol ti_sysbios_knl_Mailbox_delete=0x1001c2c5
--define_symbol ti_sysbios_knl_Semaphore_destruct=0x1001c2e1
--define_symbol ti_sysbios_BIOS_RtsGateProxy_enter__E=0x1001c249
--define_symbol ti_sysbios_knl_Task_processVitalTaskFlag__I=0x1001b739
--define_symbol ti_sysbios_knl_Mailbox_create=0x1001abdd
--define_symbol xdc_runtime_Core_deleteObject__I=0x1001c4f9
--define_symbol ti_sysbios_knl_Queue_delete=0x1001c2cd
--define_symbol ti_sysbios_family_arm_m3_Hwi_doSwiRestore__I=0x1001c1fb
--define_symbol xdc_runtime_System_atexit__E=0x1001c681
--define_symbol ti_sysbios_gates_GateMutex_Params__init__S=0x1001c179
--define_symbol ti_sysbios_knl_Clock_getTimerHandle__E=0x1001c191
--define_symbol ti_sysbios_knl_Task_enable__E=0x1001c243
--define_symbol ti_sysbios_knl_Clock_TimerProxy_getExpiredTicks__E=0x1001c2ad
--define_symbol ti_sysbios_knl_Queue_Object__destruct__S=0x1001bef5
--define_symbol ti_sysbios_knl_Clock_Object__delete__S=0x1001badd
--define_symbol ti_sysbios_gates_GateMutex_delete=0x1001c26d
--define_symbol ti_sysbios_heaps_HeapMem_restore__E=0x1001c105
--define_symbol ti_sysbios_knl_Swi_create=0x1001ad05
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_leave__E=0x1001c2a1
--define_symbol ti_sysbios_knl_Semaphore_pend__E=0x1001a0cd
--define_symbol ti_sysbios_knl_Mailbox_Instance_finalize__E=0x1001a9dd
--define_symbol xdc_runtime_Startup_startMods__I=0x1001c30d
--define_symbol ti_sysbios_heaps_HeapMem_init__I=0x1001b545
--define_symbol ti_sysbios_knl_Swi_Object__delete__S=0x1001bda9
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_enableInterrupt__E=0x1001c285
--define_symbol ti_sysbios_knl_Clock_removeI__E=0x1001c2bd
--define_symbol xdc_runtime_System_abort__E=0x1001c749
--define_symbol ti_sysbios_family_arm_m3_Hwi_dispatchC__I=0x1001aa49
--define_symbol ti_sysbios_knl_Swi_construct=0x1001b085
--define_symbol ti_sysbios_knl_Task_sleepTimeout__I=0x1001bf81
--define_symbol ti_sysbios_knl_Queue_remove__E=0x1001c121
--define_symbol ti_sysbios_knl_Semaphore_Instance_finalize__E=0x1001c0c5
--define_symbol ti_sysbios_gates_GateMutex_destruct=0x1001c271
--define_symbol ti_sysbios_knl_Task_SupportProxy_Module__startupDone__S=0x1001c2f1
--define_symbol ti_sysbios_knl_Queue_Object__delete__S=0x1001bd49
--define_symbol ti_sysbios_knl_Mailbox_Object__get__S=0x1001b89d
--define_symbol ti_sysbios_family_arm_m3_Hwi_Instance_init__E=0x1001a3c9
--define_symbol ti_sysbios_knl_Clock_delete=0x1001c2b5
--define_symbol ti_sysbios_knl_Clock_walkQueueDynamic__E=0x1001a80d
--define_symbol ti_sysbios_knl_Mailbox_Object__destruct__S=0x1001bed9
--define_symbol ti_sysbios_knl_Mailbox_post__E=0x1001a591
--define_symbol ti_sysbios_knl_Clock_Instance_init__E=0x1001b50d
--define_symbol ti_sysbios_knl_Task_allBlockedFunction__I=0x1001b365
--define_symbol ti_sysbios_knl_Task_postInit__I=0x1001a615
--define_symbol ti_sysbios_knl_Task_enter__I=0x1001be09
--define_symbol ti_sysbios_hal_Hwi_switchFromBootStack__E=0x1001c299
--define_symbol ti_sysbios_knl_Semaphore_Object__destruct__S=0x1001bd89
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_Object__create__S=0x1001c085
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_postInit__I=0x1001b769
--define_symbol ti_sysbios_knl_Swi_Module_startup__E=0x1001c237
--define_symbol ti_sysbios_gates_GateMutex_Instance_finalize__E=0x1001c075
--define_symbol xdc_runtime_Core_assignParams__I=0x1001c5f1
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_switchFromBootStack__E=0x1001c291
--define_symbol ti_sysbios_knl_Swi_post__E=0x1001b321
--define_symbol ti_sysbios_hal_Hwi_initStack=0x1001b819
--define_symbol xdc_runtime_Memory_alloc__E=0x1001c489
--define_symbol ti_sysbios_knl_Queue_next__E=0x1001c2d9
--define_symbol ti_sysbios_knl_Clock_Instance_finalize__E=0x1001bfcd
--define_symbol ti_sysbios_knl_Queue_elemClear__E=0x1001c231
--define_symbol ti_sysbios_knl_Clock_Params__init__S=0x1001c185
--define_symbol ti_sysbios_knl_Task_Instance_init__E=0x1001a25d
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_startup__E=0x1001c28d
--define_symbol ti_sysbios_knl_Task_self__E=0x1001c1e5
--define_symbol ti_sysbios_knl_Task_startup__E=0x1001c309
--define_symbol ti_sysbios_gates_GateHwi_Object__delete__S=0x1001bc09
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_startup__E=0x1001b795
--define_symbol xdc_runtime_Memory_free__E=0x1001c801
--define_symbol ti_sysbios_hal_Hwi_delete=0x1001c295
--define_symbol ti_sysbios_knl_Queue_Instance_init__E=0x1001c22b
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_Module_startup__E=0x1001ba71
--define_symbol xdc_runtime_Assert_raise__I=0x1001c5a9
--define_symbol ti_sysbios_hal_Hwi_create=0x1001ab79
--define_symbol ti_sysbios_knl_Task_destruct=0x1001c305
--define_symbol ti_sysbios_hal_Hwi_Module_startup__E=0x1001c021
--define_symbol ti_sysbios_family_arm_m3_Hwi_excHandler__I=0x1001bbc9
--define_symbol xdc_runtime_Core_destructObject__I=0x1001c7a1
--define_symbol ti_sysbios_knl_Swi_disable__E=0x1001c0d5
--define_symbol ti_sysbios_BIOS_setThreadType__E=0x1001c045
--define_symbol ti_sysbios_knl_Task_disable__E=0x1001c0f5
--define_symbol ti_sysbios_knl_Swi_Instance_init__E=0x1001aca5
--define_symbol ti_sysbios_knl_Semaphore_pendTimeout__I=0x1001b94d
--define_symbol ti_sysbios_knl_Clock_create=0x1001b3ed
--define_symbol ti_sysbios_knl_Idle_loop__E=0x1001c20b
--define_symbol ti_sysbios_gates_GateHwi_leave__E=0x1001c21f
--define_symbol ti_sysbios_family_arm_m3_Hwi_enableInterrupt__E=0x1001b2dd
--define_symbol ti_sysbios_knl_Semaphore_Params__init__S=0x1001c1c1
--define_symbol ti_sysbios_knl_Task_unblock__E=0x1001bfb5
--define_symbol ti_sysbios_knl_Swi_destruct=0x1001c2e9
--define_symbol ti_sysbios_BIOS_getCpuFreq__E=0x1001bff9
--define_symbol xdc_runtime_Memory_calloc__E=0x1001c84d
--define_symbol ti_sysbios_family_arm_m3_Hwi_startup__E=0x1001c203
--define_symbol xdc_runtime_SysCallback_exit__E=0x1001c821
--define_symbol ti_sysbios_knl_Queue_empty__E=0x1001c113
--define_symbol ti_sysbios_knl_Clock_logTick__E=0x1001be67
--define_symbol ti_sysbios_knl_Task_yield__E=0x1001b3a9
--define_symbol ti_sysbios_knl_Task_SupportProxy_getStackAlignment__E=0x1001c2f5
--define_symbol ti_sysbios_family_arm_m3_Hwi_create=0x1001ab15
--define_symbol xdc_runtime_Timestamp_SupportProxy_get32__E=0x1001c831
--define_symbol ti_sysbios_family_arm_m3_Hwi_destruct=0x1001c261
--define_symbol ti_sysbios_family_arm_m3_Hwi_doTaskRestore__I=0x1001c213
--define_symbol ti_sysbios_knl_Swi_run__I=0x1001afd9
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_Module__startupDone__S=0x1001bb49
--define_symbol xdc_runtime_Core_createObject__I=0x1001c405
--define_symbol ti_sysbios_knl_Queue_create=0x1001b921
--define_symbol ti_sysbios_hal_Hwi_Object__delete__S=0x1001bc69
--define_symbol ti_sysbios_knl_Clock_construct=0x1001b579
--define_symbol xdc_runtime_System_abortSpin__E=0x1001c899
--define_symbol ti_sysbios_family_arm_m3_Hwi_Object__destruct__S=0x1001be69
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_delete=0x1001c27d
--define_symbol ti_sysbios_gates_GateMutex_Object__create__S=0x1001b649
--define_symbol ti_sysbios_family_arm_m3_Hwi_getStackInfo__E=0x1001b465
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_enter__E=0x1001c29d
--define_symbol ti_sysbios_knl_Semaphore_post__E=0x1001ac41
--define_symbol ti_sysbios_knl_Task_exit__E=0x1001b429
--define_symbol ti_sysbios_heaps_HeapMem_Instance_init__E=0x1001b4d5
--define_symbol ti_sysbios_knl_Swi_restore__E=0x1001b5e1
--define_symbol ti_sysbios_knl_Task_startCore__E=0x1001ae75
--define_symbol ti_sysbios_knl_Semaphore_create=0x1001b5ad
--define_symbol ti_sysbios_gates_GateHwi_enter__E=0x1001c16d
--define_symbol ti_sysbios_knl_Task_blockI__E=0x1001b615
--define_symbol ti_sysbios_heaps_HeapMem_free__E=0x1001a795
--define_symbol ti_sysbios_knl_Task_Object__destruct__S=0x1001bf65
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_periodicStub__E=0x1001a469
--define_symbol ti_sysbios_hal_Hwi_Instance_init__E=0x1001b9f9
--define_symbol ti_sysbios_gates_GateHwi_query__E=0x1001c269
--define_symbol xdc_runtime_System_processAtExit__E=0x1001c6b9
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_setPeriod__E=0x1001c259
--define_symbol xdc_runtime_Error_init__E=0x1001c841
--define_symbol ti_sysbios_knl_Semaphore_Instance_init__E=0x1001bb01
--define_symbol ti_sysbios_knl_Queue_head__E=0x1001c2d5
--define_symbol xdc_runtime_Error_check__E=0x1001c7b9
--define_symbol xdc_runtime_Error_policySpin__E=0x1001c487
--define_symbol ti_sysbios_gates_GateMutex_create=0x1001b679
--define_symbol xdc_runtime_Gate_leaveSystem__E=0x1001c879
--define_symbol ti_sysbios_knl_Swi_restoreHwi__E=0x1001ad61
--define_symbol ti_sysbios_knl_Task_sleep__E=0x1001a96d
--define_symbol ti_sysbios_knl_Task_create=0x1001ae19
--define_symbol ti_sysbios_knl_Mailbox_Params__init__S=0x1001c19d
--define_symbol ti_sysbios_knl_Task_restoreHwi__E=0x1001be29
--define_symbol ti_sysbios_knl_Mailbox_postInit__I=0x1001b8c9
--define_symbol ti_sysbios_knl_Task_delete=0x1001c301
--define_symbol ti_sysbios_heaps_HeapMem_isBlocking__E=0x1001c2a5
--define_symbol ti_sysbios_knl_Clock_startI__E=0x1001a719
--define_symbol ti_sysbios_knl_Clock_start__E=0x1001bfe3
--define_symbol ti_sysbios_family_arm_m3_Hwi_Object__delete__S=0x1001bba9
--define_symbol ti_sysbios_knl_Clock_TimerProxy_getPeriod__E=0x1001c2b1
--define_symbol ti_sysbios_knl_Task_SupportProxy_start__E=0x1001c2f9
--define_symbol ti_sysbios_heaps_HeapMem_Handle__label__S=0x1001bc89
--define_symbol ti_sysbios_family_arm_m3_Hwi_delete=0x1001c25d
--define_symbol ti_sysbios_knl_Semaphore_Object__delete__S=0x1001bb25
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_getStackInfo__E=0x1001c289
--define_symbol ti_sysbios_knl_Idle_run__E=0x1001bd09
--define_symbol ti_sysbios_knl_Swi_delete=0x1001c2e5
--define_symbol xdc_runtime_Memory_valloc__E=0x1001c785
--define_symbol ti_sysbios_knl_Mailbox_Object__delete__S=0x1001bd29
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_start__E=0x1001b49d
--define_symbol ti_sysbios_family_arm_m3_Hwi_Module__startupDone__S=0x1001bb89
--define_symbol ti_sysbios_knl_Swi_startup__E=0x1001c23d
--define_symbol ti_sysbios_knl_Task_schedule__I=0x1001b175
--define_symbol ti_sysbios_gates_GateMutex_leave__E=0x1001bf9d
--define_symbol ti_sysbios_heaps_HeapMem_Object__delete__S=0x1001bca9
--define_symbol ti_sysbios_knl_Clock_TimerProxy_setNextTick__E=0x1001c0b5
--define_symbol ti_sysbios_knl_Swi_Object__get__S=0x1001b979
--define_symbol ti_sysbios_knl_Task_restore__E=0x1001ba49
--define_symbol xdc_runtime_Memory_HeapProxy_alloc__E=0x1001c889
--define_symbol ti_sysbios_gates_GateHwi_Object__create__S=0x1001ba95
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_disableInterrupt__E=0x1001c281
--define_symbol ti_sysbios_BIOS_start__E=0x1001c055
--define_symbol ti_sysbios_BIOS_exit__E=0x1001c035
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_getStackAlignment__E=0x1001c161
--define_symbol xdc_runtime_SysCallback_abort__E=0x1001c811
--define_symbol ti_sysbios_knl_Queue_destruct=0x1001c2d1
--define_symbol ti_sysbios_family_arm_m3_Hwi_postInit__I=0x1001a319
--define_symbol ti_sysbios_gates_GateMutex_Instance_init__E=0x1001bea1
--define_symbol ti_sysbios_knl_Task_Instance_finalize__E=0x1001a4fd
--define_symbol ti_sysbios_knl_Clock_TimerProxy_getCurrentTick__E=0x1001c095
--define_symbol ti_sysbios_family_arm_m3_Hwi_disableFxn__E=0x1001c149
--define_symbol xdc_runtime_Memory_HeapProxy_free__E=0x1001c88d
--define_symbol ti_sysbios_knl_Mailbox_Module_startup__E=0x1001b251
--define_symbol ti_sysbios_knl_Task_Object__delete__S=0x1001bdc9
--define_symbol ti_sysbios_gates_GateHwi_Handle__label__S=0x1001bbe9
--define_symbol xdc_runtime_Text_ropeText__E=0x1001c7e9
--define_symbol ti_sysbios_knl_Clock_destruct=0x1001c2b9
--define_symbol ti_sysbios_knl_Queue_construct=0x1001b8f5
--define_symbol ti_sysbios_family_arm_m3_Hwi_switchFromBootStack__E=0x1001c00d
--define_symbol ti_sysbios_heaps_HeapMem_Object__get__S=0x1001b871
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_create=0x1001be49
--define_symbol ti_sysbios_gates_GateMutex_query__E=0x1001c275
--define_symbol ti_sysbios_knl_Swi_schedule__I=0x1001b031
--define_symbol ti_sysbios_knl_Task_Params__init__S=0x1001c1d9
--define_symbol ti_sysbios_family_arm_m3_Hwi_Params__init__S=0x1001c13d
--define_symbol ti_sysbios_family_arm_m3_Hwi_plug__E=0x1001c065
--define_symbol xdc_runtime_System_exitSpin__E=0x1001c89b
--define_symbol ti_sysbios_gates_GateMutex_construct=0x1001b7ed
--define_symbol xdc_runtime_System_Module_GateProxy_leave__E=0x1001c895
--define_symbol ti_sysbios_knl_Mailbox_pend__E=0x1001a8fd
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_Module__startupDone__S=0x1001c265
--define_symbol xdc_runtime_Core_assignLabel__I=0x1001c6ed
--define_symbol xdc_runtime_System_Module_GateProxy_enter__E=0x1001c891
--define_symbol xdc_runtime_System_exit__E=0x1001c7d1
--define_symbol ti_sysbios_knl_Swi_Params__init__S=0x1001c1cd
--define_symbol ti_sysbios_knl_Clock_workFunc__E=0x1001a885
--define_symbol ti_sysbios_family_arm_m3_Hwi_restoreFxn__E=0x1001c219
--define_symbol ti_sysbios_family_arm_cc26xx_TimestampProvider_Module_startup__E=0x1001bb69
--define_symbol ti_sysbios_knl_Semaphore_delete=0x1001c2dd
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_getPeriod__E=0x1001c255
--define_symbol ti_sysbios_family_arm_m3_Hwi_initNVIC__E=0x1001a699
--define_symbol ti_sysbios_knl_Clock_addI__E=0x1001ba21
--define_symbol ti_sysbios_family_arm_m3_Hwi_Instance_finalize__E=0x1001aed1
--define_symbol ti_sysbios_heaps_HeapMem_alloc__E=0x1001a199
--define_symbol ti_sysbios_knl_Task_unblockI__E=0x1001b9a5
--define_symbol ti_sysbios_knl_Swi_Instance_finalize__E=0x1001bf9b
--define_symbol ti_sysbios_family_arm_m3_Hwi_disableInterrupt__E=0x1001b299
--define_symbol ti_sysbios_family_arm_m3_Hwi_enableFxn__E=0x1001c155
--define_symbol xdc_runtime_Gate_enterSystem__E=0x1001c885
--define_symbol ti_sysbios_gates_GateMutex_Object__delete__S=0x1001bab9
--define_symbol ti_sysbios_family_arm_cc26xx_TimestampProvider_get64__E=0x1001b9d1
--define_symbol ti_sysbios_knl_Mailbox_Instance_init__E=0x1001a001
--define_symbol xdc_runtime_Text_cordText__E=0x1001c71d
--define_symbol xdc_runtime_Startup_exec__E=0x1001c559
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_Module__startupDone__S=0x1001c279
--define_symbol ti_sysbios_heaps_HeapMem_getStats__E=0x1001b209
--define_symbol ti_sysbios_knl_Task_SupportProxy_swap__E=0x1001c2fd
--define_symbol xdc_runtime_Memory_getMaxDefaultTypeAlign__E=0x1001c859
--define_symbol ti_sysbios_knl_Task_Object__get__S=0x1001bde9
--define_symbol ti_sysbios_family_arm_m3_Hwi_construct=0x1001af29
--define_symbol ti_sysbios_knl_Clock_TimerProxy_Module__startupDone__S=0x1001c2a9
--define_symbol ti_sysbios_knl_Clock_Module_startup__E=0x1001bcc9
--define_symbol ti_sysbios_knl_Mailbox_construct=0x1001af81
--define_symbol ti_sysbios_knl_Task_construct=0x1001b125
--define_symbol xdc_runtime_Core_constructObject__I=0x1001c639
--define_symbol ti_sysbios_knl_Queue_dequeue__E=0x1001c1a9
--define_symbol ti_sysbios_knl_Task_Module_startup__E=0x1001adbd
--define_symbol ti_sysbios_family_arm_cc26xx_Timer_getExpiredTicks__E=0x1001c251
--define_symbol ti_sysbios_family_arm_m3_Hwi_Object__get__S=0x1001b7c1
--define_symbol ti_sysbios_knl_Mailbox_destruct=0x1001c2c9
--define_symbol xdc_runtime_System_Module_startup__E=0x1001c87f
--define_symbol ti_sysbios_knl_Swi_postInit__I=0x1001c2ed
--define_symbol ti_sysbios_family_arm_m3_Hwi_Module_startup__E=0x1001b1c1
--define_symbol ti_sysbios_gates_GateMutex_enter__E=0x1001b6a9
--define_symbol ti_sysbios_family_arm_m3_Hwi_setPriority__E=0x1001be85
--define_symbol ti_sysbios_knl_Queue_Object__get__S=0x1001bd69
--define_symbol ti_sysbios_knl_Clock_setTimeout__E=0x1001c2c1
--define_symbol ti_sysbios_knl_Task_swapReturn=0x1001ca71
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_glue=0x1001ca59
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_buildTaskStack=0x1001c96d
--define_symbol ti_sysbios_family_arm_m3_TaskSupport_swap__E=0x1001ca69
--define_symbol ti_sysbios_family_arm_m3_Hwi_excHandlerAsm__I=0x1001ca01
--define_symbol ti_sysbios_family_arm_m3_Hwi_return=0x1001ca57
--define_symbol ti_sysbios_family_arm_m3_Hwi_pendSV__I=0x1001ca3f
--define_symbol ti_sysbios_family_arm_m3_Hwi_dispatch__I=0x1001c89d
--define_symbol ti_sysbios_family_xxx_Hwi_switchAndRunFunc=0x1001ca21
--define_symbol ti_sysbios_family_arm_m3_Hwi_initStacks__E=0x1001c9b9
--define_symbol ti_sysbios_BIOS_RtsGateProxy_Object__delete__S=0x1001bab9
--define_symbol ti_sysbios_BIOS_RtsGateProxy_Params__init__S=0x1001c179
--define_symbol ti_sysbios_BIOS_RtsGateProxy_Handle__label__S=0x1001bc29
--define_symbol ti_sysbios_BIOS_RtsGateProxy_query__E=0x1001c275
--define_symbol ti_sysbios_knl_Clock_TimerProxy_startup__E=0x1001b795
--define_symbol ti_sysbios_hal_Hwi_disableInterrupt__E=0x1001c281
--define_symbol ti_sysbios_hal_Hwi_enableInterrupt__E=0x1001c285
--define_symbol ti_sysbios_hal_Hwi_getStackInfo__E=0x1001c289
--define_symbol ti_sysbios_hal_Hwi_startup__E=0x1001c28d
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_Object__delete__S=0x1001bba9
--define_symbol ti_sysbios_hal_Hwi_HwiProxy_Params__init__S=0x1001c13d
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_query__E=0x1001c275
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_Object__delete__S=0x1001bab9
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_Params__init__S=0x1001c179
--define_symbol ti_sysbios_heaps_HeapMem_Module_GateProxy_Handle__label__S=0x1001bc29
--define_symbol xdc_runtime_Timestamp_SupportProxy_get64__E=0x1001b9d1
--define_symbol xdc_runtime_Timestamp_SupportProxy_getFreq__E=0x1001c12f
--define_symbol xdc_runtime_Timestamp_get32__E=0x1001c831
--define_symbol xdc_runtime_Timestamp_get64__E=0x1001b9d1
--define_symbol xdc_runtime_Timestamp_getFreq__E=0x1001c12f
--define_symbol xdc_runtime_Memory_HeapProxy_Object__delete__S=0x1001bca9
--define_symbol xdc_runtime_Memory_HeapProxy_Handle__label__S=0x1001bc89
--define_symbol xdc_runtime_System_Module_GateProxy_Object__delete__S=0x1001bc09
--define_symbol xdc_runtime_System_Module_GateProxy_Handle__label__S=0x1001bbe9
--define_symbol xdc_runtime_System_Module_GateProxy_query__E=0x1001c269

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.drivers.pdm (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.drivers (null): */

/* Content from ti.drivers.rf (null): */

/* Content from configPkg (null): */

/* Content from xdc.services.io (null): */

/* Content from ti.targets (null): */


--define_symbol xdc_runtime_Startup__EXECFXN__C=1
--define_symbol xdc_runtime_Startup__RESETFXN__C=1


--config_search C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages/ti/sysbios/rom/cortexm/cc26xx/golden/CC26xx/
--config_def USE_TIRTOS_ROM=1

--keep __ASM__
--keep __PLAT__
--keep __ISA__
--keep __TARG__
--keep __TRDR__