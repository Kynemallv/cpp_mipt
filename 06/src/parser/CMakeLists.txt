target_sources(Calculator PRIVATE parser.cpp token_stream.cpp)
target_include_directories(Calculator PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)