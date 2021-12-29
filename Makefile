# -*- MakeFile -*-

TARGET = main

# set your MCU type here, or make command line `make MCU=IMXRT1062`
MCU = IMXRT1062
MCU_LD = core/imxrt1062.ld
MCU_DEF = ARDUINO_TEENSY40

COMPILERPATH ?= /usr/bin

OPTIONS = -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE
#
# USB Type configuration:
#   -DUSB_SERIAL
#   -DUSB_DUAL_SERIAL
#   -DUSB_TRIPLE_SERIAL
#   -DUSB_KEYBOARDONLY
#   -DUSB_TOUCHSCREEN
#   -DUSB_HID_TOUCHSCREEN
#   -DUSB_HID
#   -DUSB_SERIAL_HID
#   -DUSB_MIDI
#   -DUSB_MIDI4
#   -DUSB_MIDI16
#   -DUSB_MIDI_SERIAL
#   -DUSB_MIDI4_SERIAL
#   -DUSB_MIDI16_SERIAL
#   -DUSB_AUDIO
#   -DUSB_MIDI_AUDIO_SERIAL
#   -DUSB_MIDI16_AUDIO_SERIAL
#   -DUSB_MTPDISK
#   -DUSB_RAWHID
#   -DUSB_FLIGHTSIM
#   -DUSB_FLIGHTSIM_JOYSTICK

# options needed by many Arduino libraries to configure for Teensy model
OPTIONS += -D__$(MCU)__ -DARDUINO=10810 -DTEENSYDUINO=149 -D$(MCU_DEF)

INC = -I core -I lib -I /usr/local/include/ -I. 

# additional libraries to link
LIBS = -lm -lstdc++ -lWire -larm_cortexM7lfsp_math
LIBS_PATH = -L/usr/local/Arduino/hardware/tools/arm/arm-none-eabi/lib/ -L/home/tor/Embedded_projects/Mini_segway/lib/Wire/

# for Cortex M7 with single & double precision FPU
CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -O2 $(CPUOPTIONS) -MMD $(OPTIONS) -ffunction-sections -fdata-sections

# compiler options for C++ only
CXXFLAGS =  -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing 

# compiler options for C only
CFLAGS = 

# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPUOPTIONS) -T$(MCU_LD)

CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
SIZE = $(COMPILERPATH)/arm-none-eabi-size

BUILD_DIR = build

SRC_OBJS_C := $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(wildcard src/*.c))
SRC_OBJS_CXX := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(wildcard src/*.cpp))
CORE_OBJS_C := $(patsubst core/%.c, $(BUILD_DIR)/%.o, $(wildcard core/*.c))
CORE_OBJS_CXX := $(patsubst core/%.cpp, $(BUILD_DIR)/%.o, $(wildcard core/*.cpp))

OBJS = $(SRC_OBJS_C) $(SRC_OBJS_CXX) $(CORE_OBJS_C) $(CORE_OBJS_CXX)

 
all: $(BUILD_DIR)/$(TARGET).hex


$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	@echo "Target $@ built!"

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(MCU_LD)
	@echo "Done! Linking $(OBJS) $(LIBS)..."
	@$(CC) $(LDFLAGS) $(LIBS_PATH) -o $@ $(OBJS) $(LIBS) 

$(SRC_OBJS_C): $(BUILD_DIR)/%.o : src/%.c
	@echo "Generating $@..."
	@$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

$(SRC_OBJS_CXX): $(BUILD_DIR)/%.o : src/%.cpp
	@echo "Generating $@..."
	@$(CXX) $(INC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@    

$(CORE_OBJS_C): $(BUILD_DIR)/%.o : core/%.c
	@echo "Generating $@..."
	@$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

$(CORE_OBJS_CXX): $(BUILD_DIR)/%.o : core/%.cpp
	@echo "Generating $@..."
	@$(CXX) $(INC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 


-include $(OBJS:.o=.d)	

clean:
	cd $(BUILD_DIR) && rm -f *.o *.d $(TARGET).elf $(TARGET).hex
