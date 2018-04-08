################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/gy86.c \
../Src/main.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_hal_timebase_TIM.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/tasks.c 

OBJS += \
./Src/freertos.o \
./Src/gy86.o \
./Src/main.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_hal_timebase_TIM.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/tasks.o 

C_DEPS += \
./Src/freertos.d \
./Src/gy86.d \
./Src/main.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_hal_timebase_TIM.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTM32F103xB -DUSE_HAL_DRIVER -D__packed="__attribute__((__packed__))" -D__weak="__attribute__((weak))" -DARM_MATH_CM3 -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/CMSIS/Include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Inc" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


