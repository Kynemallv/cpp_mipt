cmake_minimum_required(VERSION 3.13)
project(Calculator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Calculator calculator_without_bugs.cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/parser)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/symbol_table)

target_include_directories(Calculator PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)