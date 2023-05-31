################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/STP/Src/Common_func.c \
../Core/STP/Src/STP_Master.c 

OBJS += \
./Core/STP/Src/Common_func.o \
./Core/STP/Src/STP_Master.o 

C_DEPS += \
./Core/STP/Src/Common_func.d \
./Core/STP/Src/STP_Master.d 


# Each subdirectory must supply rules for building sources it contributes
Core/STP/Src/%.o Core/STP/Src/%.su Core/STP/Src/%.cyclo: ../Core/STP/Src/%.c Core/STP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/Muhammed/STM32CubeIDE/workspace_1.8.0/Simple Transfer Protocol/Core/STP/Config" -I"C:/Users/Muhammed/STM32CubeIDE/workspace_1.8.0/Simple Transfer Protocol/Core/STP/Inc" -I"C:/Users/Muhammed/STM32CubeIDE/workspace_1.8.0/Simple Transfer Protocol/Core/STP/Src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-STP-2f-Src

clean-Core-2f-STP-2f-Src:
	-$(RM) ./Core/STP/Src/Common_func.cyclo ./Core/STP/Src/Common_func.d ./Core/STP/Src/Common_func.o ./Core/STP/Src/Common_func.su ./Core/STP/Src/STP_Master.cyclo ./Core/STP/Src/STP_Master.d ./Core/STP/Src/STP_Master.o ./Core/STP/Src/STP_Master.su

.PHONY: clean-Core-2f-STP-2f-Src

