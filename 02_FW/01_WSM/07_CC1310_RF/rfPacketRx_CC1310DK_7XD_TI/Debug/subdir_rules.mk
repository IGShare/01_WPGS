################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CC1310DK_7XD.obj: ../CC1310DK_7XD.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI/smartrf_settings" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="CC1310DK_7XD.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

RFQueue.obj: ../RFQueue.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI/smartrf_settings" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="RFQueue.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ccfg.obj: ../ccfg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI/smartrf_settings" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="ccfg.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-2000602831:
	@$(MAKE) -Onone -f subdir_rules.mk build-2000602831-inproc

build-2000602831-inproc: ../rfExamples.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;C:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC1310F128 -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS" --compileOptions "-mv7M3 --code_state=16 --float_support=vfplib -me --include_path=\"C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI\" --include_path=\"C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI\" --include_path=\"C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI/smartrf_settings\" --include_path=\"C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include\" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-2000602831 ../rfExamples.cfg
configPkg/compiler.opt: build-2000602831
configPkg/: build-2000602831

rfPacketRx.obj: ../rfPacketRx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI" --include_path="C:/Users/sj_be/workspace_v7/rfPacketRx_CC1310DK_7XD_TI/smartrf_settings" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="rfPacketRx.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


