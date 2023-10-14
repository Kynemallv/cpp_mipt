target_sources(Calculator PRIVATE symbol_table.cpp)
target_include_directories(Calculator PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)