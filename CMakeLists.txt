cmake_minimum_required(VERSION 3.20)
project(AstroShell)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_compile_options(-Wall -Wextra -Ofast -pedantic -std=c++17 -march=native)


set(INCLUDE_DIR /home/users/mglowacki/apps)
include_directories(${INCLUDE_DIR})

add_executable(AstroShell main.cpp)


add_subdirectory(fourier)
add_subdirectory(getogleid)
add_subdirectory(clearlightcurve)
add_subdirectory(getperiod)
add_subdirectory(phase)