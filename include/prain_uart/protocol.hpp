#pragma once

#include <cstdint>
#include <cstddef>
#include "helper.hpp"

namespace prain_uart {

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

using addr_field = limited_value<uint8_t, 3>;
using cmd_field  = limited_value<uint8_t, 15>;
using crc_field  = limited_value<uint8_t, 255>;

struct frame {
    uint64_t field;

    inline uint8_t addr() const { return READFROM(field, 0, 2); }
    inline uint8_t cmd() const { return READFROM(field, 2, 4); }
    inline uint64_t parameter() const { return READFROM(field, 6, 50); }
    inline uint8_t crc() const { return READFROM(field, 56, 8); }

    inline void set_addr(addr_field a) { WRITETO(field, 0, 2, static_cast<uint8_t>(a)); }
    inline void set_cmd(cmd_field c) { WRITETO(field, 2, 4, static_cast<uint8_t>(c)); }
    inline void set_parameter(uint64_t p) { WRITETO(field, 6, 50, p); }
    inline void set_crc(crc_field c) { WRITETO(field, 56, 8, static_cast<uint8_t>(c)); }
};

/*
struct frame {
    uint64_t field;
    FIELD(field, addr, 0, 2);
    FIELD(field, cmd, 2, 4);
    FIELD(field, parameter, 6, 50);
    FIELD(field, crc, 56, 8);
};
*/

} // namespace prain_uart
