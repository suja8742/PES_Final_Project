################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_ITM -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\board" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\source" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\drivers" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\CMSIS" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\utilities" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


