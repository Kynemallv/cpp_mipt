target_sources(${TARGET} PRIVATE parser.cpp token_stream.cpp)
target_include_directories(${TARGET} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)