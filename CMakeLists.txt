cmake_minimum_required(VERSION 3.10)
project(prain_uart VERSION 1.0.0 LANGUAGES CXX)

add_library(prain_uart
    src/decoder.cpp
    src/encoder.cpp
    src/protocol.cpp
)

target_compile_features(prain_uart PUBLIC cxx_std_17)

target_include_directories(prain_uart
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS prain_uart
    EXPORT prain_uartConfigs
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY include/
    DESTINATION include
)

add_executable(prain_testexec
    test/main.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE
	#-fno-exceptions
	#-fno-unwind-tables
	#-fno-asynchronous-unwind-tables
	-Wall
	-Wextra
	-Wpedantic
	-g3
)

target_link_libraries(prain_testexec PRIVATE prain_uart)
