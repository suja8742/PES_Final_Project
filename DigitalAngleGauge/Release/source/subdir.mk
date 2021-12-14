################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/DigitalAngleGauge.c \
../source/I2C.c \
../source/LED.c \
../source/TPM.c \
../source/calibrate.c \
../source/mma8451.c \
../source/mtb.c \
../source/retarget_itm.c \
../source/semihost_hardfault.c \
../source/state_machine.c \
../source/switch.c \
../source/systick.c \
../source/test.c 

OBJS += \
./source/DigitalAngleGauge.o \
./source/I2C.o \
./source/LED.o \
./source/TPM.o \
./source/calibrate.o \
./source/mma8451.o \
./source/mtb.o \
./source/retarget_itm.o \
./source/semihost_hardfault.o \
./source/state_machine.o \
./source/switch.o \
./source/systick.o \
./source/test.o 

C_DEPS += \
./source/DigitalAngleGauge.d \
./source/I2C.d \
./source/LED.d \
./source/TPM.d \
./source/calibrate.d \
./source/mma8451.d \
./source/mtb.d \
./source/retarget_itm.d \
./source/semihost_hardfault.d \
./source/state_machine.d \
./source/switch.d \
./source/systick.d \
./source/test.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_ITM -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\board" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\source" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\drivers" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\CMSIS" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\utilities" -I"C:\Users\Sudarshan\Documents\MCUXpressoIDE_11.2.0_4120\workspace\DigitalAngleGauge\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


