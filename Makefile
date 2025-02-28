# MCU and programmer settings
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyACM0  # Change based on your system
BAUD = 115200
PROGRAMMER = arduino

# Compiler and linker settings
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

# File names
TARGET = servo
SRC = $(TARGET).c
OBJ = $(TARGET).o
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Compilation and linking
all: $(HEX)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $(OBJ) $(SRC)

$(ELF): $(OBJ)
	$(CC) -mmcu=$(MCU) -o $(ELF) $(OBJ)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $(ELF) $(HEX)

# Upload to Arduino
upload: $(HEX)
	avrdude -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):i

# Clean build files
clean:
	rm -f $(OBJ) $(ELF) $(HEX)
