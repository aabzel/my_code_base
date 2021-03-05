################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utils_stm32/subdir.mk
-include utilities/subdir.mk
-include components/tests/test_sd_card/subdir.mk
-include components/lib/unit_test/src/subdir.mk
-include components/lib/stm32_tim/src/subdir.mk
-include components/lib/stm32_spi/src/subdir.mk
-include components/lib/stm32_gpio/src/subdir.mk
-include components/lib/sd_card/subdir.mk
-include components/lib/diag_page/subdir.mk
-include com_utils/subdir.mk
-include bsp/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
stm32_vl_discovery.hex \

SECONDARY_SIZE += \
stm32_vl_discovery.siz \


# All Target
all: stm32_vl_discovery.elf secondary-outputs

# Tool invocations
stm32_vl_discovery.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "C:\1_lessons\C_programming_language\trainings\training\stm32_vl_discovery\STM32F100XB_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,"stm32_vl_discovery.map" -o "stm32_vl_discovery.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

stm32_vl_discovery.hex: stm32_vl_discovery.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "stm32_vl_discovery.elf"  "stm32_vl_discovery.hex"
	@echo 'Finished building: $@'
	@echo ' '

stm32_vl_discovery.siz: stm32_vl_discovery.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "stm32_vl_discovery.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) stm32_vl_discovery.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
