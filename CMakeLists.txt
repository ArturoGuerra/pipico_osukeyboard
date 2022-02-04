cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
project(osukeyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
        main.cpp
        leds.cpp
        buttons.cpp
        usb_hid.cpp
        usb_descriptors.c)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        pico_stdlib
        hardware_pio
        tinyusb_device
        tinyusb_board)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/buttons.pio)
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/leds.pio)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})
