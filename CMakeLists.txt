cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(eeprom C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(eeprom
	./src/main.cpp
	)

target_link_libraries(eeprom pico_stdlib)

pico_enable_stdio_usb(eeprom 1)
pico_enable_stdio_uart(eeprom 1)

pico_add_extra_outputs(eeprom)