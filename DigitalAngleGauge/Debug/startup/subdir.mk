################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

OBJS += \
./startup/startup_mkl25z4.o 

C_DEPS += \
./startup/startup_mkl25z4.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_ITM -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\board" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\source" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\drivers" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\CMSIS" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\utilities" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Final_Project\DigitalAngleGauge\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


