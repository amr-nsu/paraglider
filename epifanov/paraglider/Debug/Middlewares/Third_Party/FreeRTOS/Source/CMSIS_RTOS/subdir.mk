################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTM32F103xB -DUSE_HAL_DRIVER -D__packed="__attribute__((__packed__))" -D__weak="__attribute__((weak))" -DARM_MATH_CM3 -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/CMSIS/Include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Inc" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/rost/Studying/Diplom/Program support/paraglider.git/trunk/epifanov/paraglider/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


