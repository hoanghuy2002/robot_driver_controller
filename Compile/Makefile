.PHONY: build clean flash test

INC_DIR :=./../Drivers/Header ./../Common/Header
SRC_DIR :=./../Drivers/Source ./../Common/Source ./../Main

INC_FILES := $(foreach INC_DIR,$(INC_DIR),$(wildcard $(INC_DIR)/*h))
SRC_PATH := $(foreach SRC_DIR,$(SRC_DIR), $(wildcard $(SRC_DIR)/*.c))
SRC_FILES := $(notdir $(SRC_PATH))
OBJ_FILES := $(subst .c,.o,$(SRC_FILES))
OBJ_PATH := $(foreach OBJ_FILES, $(OBJ_FILES), ./../Object/$(OBJ_FILES))

vpath %.c $(SRC_DIR)

%.o: %.c 
	arm-none-eabi-gcc -c $< -mcpu=cortex-m3 -mthumb -std=gnu11 -mfloat-abi=soft -Wall -o ./../Object/$@ -I$(INC_DIR)

build:$(OBJ_FILES)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft --specs=nano.specs -T STM32F103_LinkerScript.ld $(OBJ_PATH) -Wl,-Map=./../Output/final.map -lm -o ./../Output/final.elf 
	arm-none-eabi-objcopy -O ihex  ./../Output/final.elf ./../Output/final.hex 
	arm-none-eabi-objcopy -O binary ./../Output/final.elf ./../Output/final.bin
	arm-none-eabi-objdump.exe -D ./../Output/final.elf > ./../Output/finalmap
	
flash:
	openocd -f board/stm32f103c8_blue_pill.cfg


clean: 
	rm ./../Object/*
	rm ./../Output/*

log: 
	@echo	${INC_FILES} 