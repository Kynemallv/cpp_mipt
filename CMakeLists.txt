cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(
    ${LIB_DIR}
)

add_subdirectory(06)
add_subdirectory(11)
add_subdirectory(12-13)
add_subdirectory(14)