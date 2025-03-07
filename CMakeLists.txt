cmake_minimum_required(VERSION 3.10)
project(pren_uart VERSION 1.0.0 LANGUAGES CXX)

add_library(my_uart_protocol
    src/decoder.cpp
    src/encoder.cpp
    src/protocol.cpp
)

target_compile_features(pren_uart PUBLIC cxx_std_17)

target_include_directories(pren_uart
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS pren_uart
    EXPORT pren_uartConfigs
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY include/
    DESTINATION include
)
