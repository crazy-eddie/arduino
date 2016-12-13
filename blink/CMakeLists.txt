cmake_minimum_required(VERSION 3.5)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)

Project(blink)

add_subdirectory(src)
