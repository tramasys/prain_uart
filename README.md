# prain_uart

A C++ library providing an encoder and decoder for our 64-bit UART protocol used in the PREN project.

## Features

- 64-bit fixed-size frames
- Address (2 bits), Command (4 bits), Parameter/Reserved (50 bits), CRC-8 (8 bits)
- CMake-based build and integration

## Building & Installing

1. Clone or copy this `prain_uart` folder into your workspace.
2. From the `prain_uart` directory:
```bash
cmake -S . -B build # -DCMAKE_BUILD_TYPE=Debug
cmake --build build
# or on linux: cmake --build build -- -j$(nproc)
```

Building for 32bit architectures:
```bash
cmake -S . -B build32 -DCMAKE_CXX_FLAGS="-m32" -DCMAKE_EXE_LINKER_FLAGS="-m32"
cmake --build build32
```
