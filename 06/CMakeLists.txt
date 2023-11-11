cmake_minimum_required(VERSION 3.13)

set(TARGET "calculator")
project(${TARGET} VERSION 1.0)

add_executable(${TARGET} calculator_without_bugs.cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/symbol_table)

target_include_directories(${TARGET} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)