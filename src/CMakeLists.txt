cmake_minimum_required(VERSION 3.15)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(DongOS)

## Setup cross-compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i686)

ENABLE_LANGUAGE(ASM)

set(TOOLS $ENV{HOME}/opt/cross)
set(CMAKE_C_COMPILER ${TOOLS}/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER ${TOOLS}/bin/i686-elf-g++)
set(CMAKE_ASM_COMPILER ${TOOLS}/bin/i686-elf-as)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -D__is_libk")
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra")

set(KERNEL_BIN "DongOS.bin")
set(KERNEL_ISO ${CMAKE_PROJECT_NAME}.iso)


file(GLOB_RECURSE KSRC kernel/src/*.cpp kernel/src/*.c kernel/src/*.s)
file(GLOB_RECURSE KHDR kernel/include/*.hpp kernel/include/*.h)
## Building the kernel binary
add_executable(${KERNEL_BIN} kernel/src/kernel.c ${KSRC} ${KHDR})

set_target_properties(${KERNEL_BIN} PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -ffreestanding -O2 -nostdlib -lgcc")
add_custom_command(TARGET ${KERNEL_BIN} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BIN} ${CMAKE_SOURCE_DIR}/bin/)

## Generating the ISO file
add_custom_target(${KERNEL_ISO}
        COMMAND ../generate-iso.sh
        COMMENT "Generating the kernel bootable iso file"
        BYPRODUCTS ${KERNEL_ISO})
add_dependencies(DongOS.iso DongOS.bin)
add_custom_command(TARGET ${KERNEL_ISO} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_ISO} ${CMAKE_SOURCE_DIR}/bin/)



