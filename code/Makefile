TARGET=main
MCU=-mthumb -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16

SRC_DIR=src
INCLUDE_DIR=include
LDSCRIPT_DIR=ldscript
BIN_DIR=bin

F3_HAL_SRC_DIR=hal_src
CMSIS_INCLUDE_DIR=${STM32_CMSIS_DIR}/include
F3_CMSIS_INCLUDE_DIR=${STM32F3_CMSIS_DIR}/include
F3_HAL_INCLUDE_DIR=${STM32F3_HAL_DIR}/include

FREERTOS_SRC_DIR=freertos_src
FREERTOS_INCLUDE_DIR=${FREERTOS_DIR}/include
FREERTOS_PORT_INCLUDE_DIR=${FREERTOS_DIR}/portable/GCC/ARM_CM4F

SRC=$(wildcard $(SRC_DIR)/*)
LDSCRIPT=STM32F303RETx_FLASH.ld
BIN=$(BIN_DIR)/$(TARGET).bin
ELF=$(BIN_DIR)/$(TARGET).elf

HAL_SRC=$(wildcard $(F3_HAL_SRC_DIR)/*.c)
FREERTOS_SRC=$(wildcard $(FREERTOS_SRC_DIR)/*.c)

LDFLAGS=-Wl,--gc-sections,-lgcc,-lc,-lnosys
CPPFLAGS=-I $(INCLUDE_DIR) -I $(CMSIS_INCLUDE_DIR) -I $(F3_CMSIS_INCLUDE_DIR) -I $(F3_HAL_INCLUDE_DIR) -I $(FREERTOS_INCLUDE_DIR) -I $(FREERTOS_PORT_INCLUDE_DIR)
CFLAGS=-g -Wall -Os -ffunction-sections -fdata-sections
GDBFLAGS=--tui

.PHONY: flash debug tag clean 

.SECONDARY:

all: $(BIN)

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $< $@

$(ELF): $(SRC)
	arm-none-eabi-gcc $(CFLAGS) $(MCU) $(CPPFLAGS) -T $(LDSCRIPT) -L $(LDSCRIPT_DIR) $(LDFLAGS) $(HAL_SRC) $(FREERTOS_SRC) $^ -o $@

flash: $(BIN)
	st-flash write $< 0x8000000

debug: $(ELF)
	arm-none-eabi-gdb $(GDBFLAGS) $(ELF)

tag:
	ctags -R .

clean:
	rm $(BIN) $(ELF)
