################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_assert.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_cmu.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_ebi.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_emu.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_gpio.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_system.c \
C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_usart.c 

OBJS += \
./emlib/em_assert.o \
./emlib/em_cmu.o \
./emlib/em_ebi.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_system.o \
./emlib/em_usart.o 

C_DEPS += \
./emlib/em_assert.d \
./emlib/em_cmu.d \
./emlib/em_ebi.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_system.d \
./emlib/em_usart.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_assert.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_assert.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_assert.d" -MT"emlib/em_assert.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_ebi.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_ebi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_ebi.d" -MT"emlib/em_ebi.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_system.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_system.d" -MT"emlib/em_system.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_usart.o: C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/src/em_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/examples/blink" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/EFM32GG_DK3750/config" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_usart.d" -MT"emlib/em_usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


