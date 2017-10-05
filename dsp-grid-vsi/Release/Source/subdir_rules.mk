################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
0Main.obj: ../Source/0Main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/0Main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ADC.obj: ../Source/ADC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ADC.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Crc.obj: ../Source/Crc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/Crc.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_ADC_cal.obj: ../Source/DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_ADC_cal.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: ../Source/DSP2833x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_GlobalVariableDefs.obj: ../Source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_SysCtrl.obj: ../Source/DSP2833x_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_SysCtrl.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_usDelay.obj: ../Source/DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_usDelay.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

EPWM.obj: ../Source/EPWM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/EPWM.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ESTAGIO_0.obj: ../Source/ESTAGIO_0.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ESTAGIO_0.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ESTAGIO_1.obj: ../Source/ESTAGIO_1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ESTAGIO_1.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ESTAGIO_2.obj: ../Source/ESTAGIO_2.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ESTAGIO_2.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

EXTMEM.obj: ../Source/EXTMEM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/EXTMEM.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

GPIO.obj: ../Source/GPIO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/GPIO.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

GridVsiFunctions.obj: ../Source/GridVsiFunctions.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/GridVsiFunctions.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

INTERRUPT.obj: ../Source/INTERRUPT.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/INTERRUPT.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MAIN_ISR.obj: ../Source/MAIN_ISR.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/MAIN_ISR.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MEM_COPY.obj: ../Source/MEM_COPY.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/MEM_COPY.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MODULATION.obj: ../Source/MODULATION.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/MODULATION.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSO.obj: ../Source/MSO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/MSO.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ModbusData.obj: ../Source/ModbusData.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ModbusData.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ModbusDataHandler.obj: ../Source/ModbusDataHandler.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ModbusDataHandler.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ModbusDataMap.obj: ../Source/ModbusDataMap.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ModbusDataMap.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ModbusSlave.obj: ../Source/ModbusSlave.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ModbusSlave.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PIE.obj: ../Source/PIE.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/PIE.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PROTECAO.obj: ../Source/PROTECAO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/PROTECAO.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SYSTEM.obj: ../Source/SYSTEM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/SYSTEM.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Serial.obj: ../Source/Serial.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/Serial.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Timer.obj: ../Source/Timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/Timer.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

VARS.obj: ../Source/VARS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="/packages/ti/xdais" --include_path="../Include" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/VARS.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


