#pragma once

#include <cstdint>
#include <cstddef>

namespace pren_uart {

constexpr std::size_t FRAME_SIZE_BITS = 64;
constexpr std::size_t ADDR_SIZE_BITS  = 2;
constexpr std::size_t CMD_SIZE_BITS   = 4;
constexpr std::size_t PARAM_SIZE_BITS = 50;
constexpr std::size_t CRC_SIZE_BITS   = 8;

enum class address : uint8_t {
    raspberry_hat   = 0b00,
    motion_ctrl     = 0b01,
    grip_ctrl       = 0b11
};

enum class command : uint8_t {
    move            = 0x0,
    reverse         = 0x1,
    turn            = 0x2,
    rotate          = 0x3,
    stop_normal     = 0x4,
    stop_emergency  = 0x5,
    info            = 0x6,
    ping            = 0x7,
    error_check     = 0x8
};

struct frame {
    uint8_t addr;
    uint8_t cmd;
    uint64_t parameter; // TODO: placeholder
    uint8_t crc;
};

} // namespace pren_uart
