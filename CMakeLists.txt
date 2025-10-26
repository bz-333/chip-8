cmake_minimum_required(VERSION 3.22)
project(CHIP8Emulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

find_package(SDL2 REQUIRED)

add_executable(chip-8 src/main.cpp src/emulator.cpp src/renderer.cpp src/input_handler.cpp src/keypad.cpp)

target_include_directories(chip-8 PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(chip-8 PRIVATE ${SDL2_LIBRARIES})