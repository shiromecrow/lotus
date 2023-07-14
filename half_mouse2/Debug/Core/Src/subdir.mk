################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CL_encoder.c \
../Core/Src/CL_gyro.c \
../Core/Src/CL_sensor.c \
../Core/Src/Control_motor.c \
../Core/Src/FF_motor.c \
../Core/Src/PID_EncoderGyro.c \
../Core/Src/PID_wall.c \
../Core/Src/PL_LED.c \
../Core/Src/PL_encoder.c \
../Core/Src/PL_flash.c \
../Core/Src/PL_gyro.c \
../Core/Src/PL_motor.c \
../Core/Src/PL_sensor.c \
../Core/Src/PL_timer.c \
../Core/Src/adc.c \
../Core/Src/cal_acceleration.c \
../Core/Src/dma.c \
../Core/Src/fail_safe.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/maze_Turning.c \
../Core/Src/maze_strategy.c \
../Core/Src/maze_wall.c \
../Core/Src/mode_select.c \
../Core/Src/record.c \
../Core/Src/spi.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/tim.c \
../Core/Src/turning_parameter.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/CL_encoder.o \
./Core/Src/CL_gyro.o \
./Core/Src/CL_sensor.o \
./Core/Src/Control_motor.o \
./Core/Src/FF_motor.o \
./Core/Src/PID_EncoderGyro.o \
./Core/Src/PID_wall.o \
./Core/Src/PL_LED.o \
./Core/Src/PL_encoder.o \
./Core/Src/PL_flash.o \
./Core/Src/PL_gyro.o \
./Core/Src/PL_motor.o \
./Core/Src/PL_sensor.o \
./Core/Src/PL_timer.o \
./Core/Src/adc.o \
./Core/Src/cal_acceleration.o \
./Core/Src/dma.o \
./Core/Src/fail_safe.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/maze_Turning.o \
./Core/Src/maze_strategy.o \
./Core/Src/maze_wall.o \
./Core/Src/mode_select.o \
./Core/Src/record.o \
./Core/Src/spi.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/tim.o \
./Core/Src/turning_parameter.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/CL_encoder.d \
./Core/Src/CL_gyro.d \
./Core/Src/CL_sensor.d \
./Core/Src/Control_motor.d \
./Core/Src/FF_motor.d \
./Core/Src/PID_EncoderGyro.d \
./Core/Src/PID_wall.d \
./Core/Src/PL_LED.d \
./Core/Src/PL_encoder.d \
./Core/Src/PL_flash.d \
./Core/Src/PL_gyro.d \
./Core/Src/PL_motor.d \
./Core/Src/PL_sensor.d \
./Core/Src/PL_timer.d \
./Core/Src/adc.d \
./Core/Src/cal_acceleration.d \
./Core/Src/dma.d \
./Core/Src/fail_safe.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/maze_Turning.d \
./Core/Src/maze_strategy.d \
./Core/Src/maze_wall.d \
./Core/Src/mode_select.d \
./Core/Src/record.d \
./Core/Src/spi.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/tim.d \
./Core/Src/turning_parameter.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G491xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CL_encoder.d ./Core/Src/CL_encoder.o ./Core/Src/CL_encoder.su ./Core/Src/CL_gyro.d ./Core/Src/CL_gyro.o ./Core/Src/CL_gyro.su ./Core/Src/CL_sensor.d ./Core/Src/CL_sensor.o ./Core/Src/CL_sensor.su ./Core/Src/Control_motor.d ./Core/Src/Control_motor.o ./Core/Src/Control_motor.su ./Core/Src/FF_motor.d ./Core/Src/FF_motor.o ./Core/Src/FF_motor.su ./Core/Src/PID_EncoderGyro.d ./Core/Src/PID_EncoderGyro.o ./Core/Src/PID_EncoderGyro.su ./Core/Src/PID_wall.d ./Core/Src/PID_wall.o ./Core/Src/PID_wall.su ./Core/Src/PL_LED.d ./Core/Src/PL_LED.o ./Core/Src/PL_LED.su ./Core/Src/PL_encoder.d ./Core/Src/PL_encoder.o ./Core/Src/PL_encoder.su ./Core/Src/PL_flash.d ./Core/Src/PL_flash.o ./Core/Src/PL_flash.su ./Core/Src/PL_gyro.d ./Core/Src/PL_gyro.o ./Core/Src/PL_gyro.su ./Core/Src/PL_motor.d ./Core/Src/PL_motor.o ./Core/Src/PL_motor.su ./Core/Src/PL_sensor.d ./Core/Src/PL_sensor.o ./Core/Src/PL_sensor.su ./Core/Src/PL_timer.d ./Core/Src/PL_timer.o ./Core/Src/PL_timer.su ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/cal_acceleration.d ./Core/Src/cal_acceleration.o ./Core/Src/cal_acceleration.su ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fail_safe.d ./Core/Src/fail_safe.o ./Core/Src/fail_safe.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/maze_Turning.d ./Core/Src/maze_Turning.o ./Core/Src/maze_Turning.su ./Core/Src/maze_strategy.d ./Core/Src/maze_strategy.o ./Core/Src/maze_strategy.su ./Core/Src/maze_wall.d ./Core/Src/maze_wall.o ./Core/Src/maze_wall.su ./Core/Src/mode_select.d ./Core/Src/mode_select.o ./Core/Src/mode_select.su ./Core/Src/record.d ./Core/Src/record.o ./Core/Src/record.su ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/turning_parameter.d ./Core/Src/turning_parameter.o ./Core/Src/turning_parameter.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

