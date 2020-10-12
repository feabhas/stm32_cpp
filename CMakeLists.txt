cmake_minimum_required(VERSION 3.2)

# cludge for cmake cross-compiler issue trying to build a simple main see:
# https://stackoverflow.com/questions/53633705/cmake-the-c-compiler-is-not-able-to-compile-a-simple-test-program
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(feabhas-stm32f407 VERSION 1.0)

enable_language(CXX C ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# asm used in some system files requires gun99 directive set(CMAKE_C_FLAGS
# "${CMAKE_C_FLAGS} -std=gnu99")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(drivers)
add_subdirectory(system)
# GLOB is generally not good practice, but for our exercises then okay as we
# want to include all files in the src dir
file(GLOB SRCS src/*.cpp)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE} ${SRCS} ${DRIVER_FILES} ${SYSTEM_FILES})

target_include_directories(${EXECUTABLE} PRIVATE drivers/ src/
                                                 ${SYSTEM_INCLUDE_DIRS})

target_compile_definitions(
  ${EXECUTABLE}
  PRIVATE -DDEBUG
          -DUSE_FULL_ASSERT
          -DSTM32F407xx
          -DTRACE
          -DOS_USE_TRACE_SEMIHOSTING_DEBUG
          -DOS_USE_TRACE_SEMIHOSTING_STDOUT
          -DOS_USE_SEMIHOSTING)

# only set for debug at the moment
target_compile_options(
  ${EXECUTABLE}
  PRIVATE -mcpu=cortex-m4
          -mthumb
          -mfpu=fpv4-sp-d16
          -mfloat-abi=hard
          -fdata-sections
          -ffunction-sections
          -Wall
          $<$<CONFIG:Debug>:-Og>)

target_link_options(
  ${EXECUTABLE}
  PRIVATE
  -T${CMAKE_SOURCE_DIR}/ldscripts/mem-qemu.ld
  -T${CMAKE_SOURCE_DIR}/ldscripts/sections.ld
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -nostartfiles
  -specs=nano.specs
  -specs=rdimon.specs
  -Wl,--build-id
  -lc
  -lm
  # -lnosys
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections)

# Print executable size
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(
  TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
