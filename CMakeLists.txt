cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_TOOLCHAIN_FILE "/home/tor/VSCodeProjects/cmake_toolchains/teensy4_tools.cmake" CACHE PATH "Toolchain file")

project(Mini_segway VERSION 0.1.0)

file(GLOB SRC_H CONFIGURE_DEPENDS "src/*.h" "core/*.h")
file(GLOB_RECURSE SRC_CPPC CONFIGURE_DEPENDS "src/*.c" "src/*.cpp" "core/*.c" "core/*.cpp")
file(GLOB SRC_LIBWIRE CONFIGURE_DEPENDS "lib/Wire/*.h" "lib/Wire/*.cpp")

set(SRC ${SRC_H} ${SRC_CPPC})

set(MCU IMXRT1062)
set(MCU_LD ${CMAKE_SOURCE_DIR}/core/imxrt1062.ld)
set(MCU_DEF ARDUINO_TEENSY40)

set(CPUOPTIONS -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb)

add_executable(main2.elf ${SRC})
add_library(Wire STATIC ${SRC_LIBWIRE})

# CPU FLAGS
target_compile_definitions(main2.elf PUBLIC -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH
                          -DUSING_MAKEFILE -D__${MCU}__ -DARDUINO=10810 -DTEENSYDUINO=149 -D${MCU_DEF})

target_compile_options(main2.elf PUBLIC -Wall -g -O2 ${CPUOPTIONS} -MMD -ffunction-sections -fdata-sections
                      -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing)

target_link_options(main2.elf PUBLIC -Os -Wl,--gc-sections,--relax -specs=nano.specs ${CPUOPTIONS} -T${MCU_LD})

# Wire LIB FLAGS
target_compile_definitions(Wire PUBLIC -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH
                          -DUSING_MAKEFILE -D__${MCU}__ -DARDUINO=10810 -DTEENSYDUINO=149 -D${MCU_DEF})

target_compile_options(Wire PUBLIC -Wall -g -O2 ${CPUOPTIONS} -MMD -ffunction-sections -fdata-sections
                      -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing)

target_link_options(Wire PUBLIC -Os -Wl,--gc-sections,--relax -specs=nano.specs ${CPUOPTIONS} -T${MCU_LD})

# Include and lib dirs
target_link_directories(main2.elf BEFORE PUBLIC /home/tor/Downloads/Arduino/hardware/tools/arm/arm-none-eabi/lib lib/Wire/)

target_include_directories(main2.elf PUBLIC /usr/local/include/ /home/tor/VSCodeProjects/Embedded/Mini_segway/src/ 
                           /home/tor/VSCodeProjects/Embedded/Mini_segway/core/ 
                           /home/tor/VSCodeProjects/Embedded/Mini_segway/lib)

target_include_directories(Wire PUBLIC /home/tor/VSCodeProjects/Embedded/Mini_segway/src
                           /home/tor/VSCodeProjects/Embedded/Mini_segway/core)

target_link_libraries(main2.elf m stdc++ Wire arm_cortexM7lfsp_math)

add_custom_target(main2.hex ALL DEPENDS main2.elf)
add_custom_command(TARGET main2.hex PRE_BUILD COMMAND ${CMAKE_C_OBJCOPY} ARGS -O ihex -R .eeprom main2.elf main2.hex)
