cmake_minimum_required(VERSION 3.20)

project("Vector" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


cmake_path(SET LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(
    ${LIB_DIR}
)

add_executable("Vector" main.cpp vector.h ${LIB_DIR}/Tracer_lib/tracer.cpp ${LIB_DIR}/Tracer_lib/tracer.h)