cmake_minimum_required(VERSION 3.10)
project(prain_uart VERSION 1.0.0 LANGUAGES CXX)

add_library(prain_uart
    src/decoder.cpp
    src/encoder.cpp
    src/protocol.cpp
    src/crc.cpp
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

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.tar.gz
)

# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(prain_testexec
    test/main.cpp
)

target_compile_options(prain_testexec PRIVATE
	#-fno-exceptions
	#-fno-unwind-tables
	#-fno-asynchronous-unwind-tables
	-Wall
	-Wextra
	-Wpedantic
	-g3
)

add_executable(prain_unittests
    test/unit_tests.cpp
)

target_compile_options(prain_unittests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -g3
)

target_link_libraries(prain_unittests PRIVATE prain_uart gtest gtest_main)

add_custom_command(
    TARGET prain_unittests
    POST_BUILD
    COMMAND $<TARGET_FILE:prain_unittests>
    COMMENT "Running unit tests after build"
)

add_test(NAME PrainUartUnitTests COMMAND prain_unittests)

if(STATIC_LINK)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libstdc++ -static-libgcc")
endif()

target_link_libraries(prain_testexec PRIVATE prain_uart)
