################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"../F28335.cmd" \
"../DSP2833x_Headers_nonBIOS.cmd" \
"../Libs/rts2800_fpu32.lib" \
"../Libs/rts2800_fpu32_fast_supplement.lib" \
"../Libs/rts2800_ml.lib" \
"./0Main.obj" \
"./ADC.obj" \
"./Crc.obj" \
"./DSP2833x_ADC_cal.obj" \
"./DSP2833x_CodeStartBranch.obj" \
"./DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_SysCtrl.obj" \
"./DSP2833x_usDelay.obj" \
"./EPWM.obj" \
"./ESTAGIO_0.obj" \
"./ESTAGIO_1.obj" \
"./ESTAGIO_2.obj" \
"./EXTMEM.obj" \
"./GPIO.obj" \
"./GridVsiFunctions.obj" \
"./INTERRUPT.obj" \
"./MAIN_ISR.obj" \
"./MEM_COPY.obj" \
"./MODULATION.obj" \
"./MSO.obj" \
"./ModbusData.obj" \
"./ModbusDataHandler.obj" \
"./ModbusDataMap.obj" \
"./ModbusSlave.obj" \
"./PIE.obj" \
"./PROTECAO.obj" \
"./SYSTEM.obj" \
"./Serial.obj" \
"./Timer.obj" \
"./VARS.obj" \
$(GEN_CMDS__FLAG) \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Libs/subdir_vars.mk
-include Source/subdir_vars.mk
-include subdir_rules.mk
-include Libs/subdir_rules.mk
-include Source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
DSP_INVERSOR_2.out \

EXE_OUTPUTS__QUOTED += \
"DSP_INVERSOR_2.out" \

BIN_OUTPUTS += \
DSP_INVERSOR_2.hex \

BIN_OUTPUTS__QUOTED += \
"DSP_INVERSOR_2.hex" \


# All Target
all: DSP_INVERSOR_2.out

# Tool invocations
DSP_INVERSOR_2.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --define="_DEBUG" --define="LARGE_MODEL" --define=FLASH=1 --define=DEBUG=0 --display_error_number --diag_warning=225 --diag_wrap=off -z -m"DSP_INVERSOR_2.map" --stack_size=0x380 --warn_sections -i"C:/Users/Henrique/Desktop/dsp-inv-inep/dsp-grid-vsi" -i"J:/Dropbox/Dropbox/SourceTree/dsp-inv-inep/uGrid2_MODBUS_10072015/DSP_INVERSOR_2" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="dsp-grid-vsi_linkInfo.xml" --entry_point=code_start --rom_model -o "DSP_INVERSOR_2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

DSP_INVERSOR_2.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.1.LTS/bin/hex2000"  -o "DSP_INVERSOR_2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Source\0Main.d" "Source\ADC.d" "Source\Crc.d" "Source\DSP2833x_GlobalVariableDefs.d" "Source\DSP2833x_SysCtrl.d" "Source\EPWM.d" "Source\ESTAGIO_0.d" "Source\ESTAGIO_1.d" "Source\ESTAGIO_2.d" "Source\EXTMEM.d" "Source\GPIO.d" "Source\GridVsiFunctions.d" "Source\INTERRUPT.d" "Source\MAIN_ISR.d" "Source\MEM_COPY.d" "Source\MODULATION.d" "Source\MSO.d" "Source\ModbusData.d" "Source\ModbusDataHandler.d" "Source\ModbusDataMap.d" "Source\ModbusSlave.d" "Source\PIE.d" "Source\PROTECAO.d" "Source\SYSTEM.d" "Source\Serial.d" "Source\Timer.d" "Source\VARS.d" 
	-$(RM) "0Main.obj" "ADC.obj" "Crc.obj" "DSP2833x_ADC_cal.obj" "DSP2833x_CodeStartBranch.obj" "DSP2833x_GlobalVariableDefs.obj" "DSP2833x_SysCtrl.obj" "DSP2833x_usDelay.obj" "EPWM.obj" "ESTAGIO_0.obj" "ESTAGIO_1.obj" "ESTAGIO_2.obj" "EXTMEM.obj" "GPIO.obj" "GridVsiFunctions.obj" "INTERRUPT.obj" "MAIN_ISR.obj" "MEM_COPY.obj" "MODULATION.obj" "MSO.obj" "ModbusData.obj" "ModbusDataHandler.obj" "ModbusDataMap.obj" "ModbusSlave.obj" "PIE.obj" "PROTECAO.obj" "SYSTEM.obj" "Serial.obj" "Timer.obj" "VARS.obj" 
	-$(RM) "Source\DSP2833x_ADC_cal.d" "Source\DSP2833x_CodeStartBranch.d" "Source\DSP2833x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

