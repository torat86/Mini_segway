# -*- MakeFile -*-

# set your MCU type here, or make command line `make MCU=IMXRT1062`
MCU = IMXRT1062
MCU_LD = core/imxrt1062.ld
MCU_DEF = ARDUINO_TEENSY40

COMPILERPATH ?= /usr/bin

OPTIONS = -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE


# options needed by many Arduino libraries to configure for Teensy model
OPTIONS += -D__$(MCU)__ -DARDUINO=10810 -DTEENSYDUINO=149 -D$(MCU_DEF)

INC = -I ../../core -I /usr/local/include/ -I. 

# for Cortex M7 with single & double precision FPU
CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -O2 $(CPUOPTIONS) -MMD $(OPTIONS) -ffunction-sections -fdata-sections

# compiler options for C++ only
CXXFLAGS =  -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing 

# compiler options for C only
CFLAGS = 


CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++

C_FILES = $(wildcard *.c)
CXX_FILES = $(wildcard *.cpp)

OBJS_C := $(C_FILES:.c=.o) 
OBJS_CXX := $(CXX_FILES:.cpp=.o)

OBJS := $(OBJS_C) $(OBJS_CXX)

all: libGPT.a

libGPT.a: $(OBJS)
	ar rcs $@ $+
	
$(OBJS_C): %.o : %.c
	@echo "Building $@ from $<..."
	@$(CC) $(INC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 
    
$(OBJS_CXX): %.o : %.cpp
	@echo "Building $@ from $<..."
	@$(CXX) $(INC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@    
 
 
-include $(OBJS:.o=.d)	

clean:
	rm -f *.o *.d 
 
 
 
 
 
 
    
    
    
    
