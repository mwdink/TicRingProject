################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/uart/subdir.mk
-include src/subdir.mk
-include src/lcdLibrary/subdir.mk
-include src/fixUps/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
TicRingEmbedded.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: TicRingEmbedded.elf secondary-outputs

# Tool invocations
TicRingEmbedded.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,TicRingEmbedded.map,--cref -L"C:\Users\dinkem1\Codebase\TicRingProject\TicRingEmbedded\lib\Release" -mmcu=atmega328p -o"TicRingEmbedded.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TicRingEmbedded.lss: TicRingEmbedded.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S TicRingEmbedded.elf  >"TicRingEmbedded.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: TicRingEmbedded.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p TicRingEmbedded.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) TicRingEmbedded.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
