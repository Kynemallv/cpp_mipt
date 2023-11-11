target_sources(${TARGET} PRIVATE symbol_table.cpp)
target_include_directories(${TARGET} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)