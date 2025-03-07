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
    RASPBERRY_HAT   = 0b00,
    MOTION_CTRL     = 0b01,
    GRIP_CTRL       = 0b11
};

enum class command : uint8_t {
    MOVE            = 0x0,
    REVERSE         = 0x1,
    TURN            = 0x2,
    ROTATE          = 0x3,
    STOP_NORMAL     = 0x4,
    STOP_EMERGENCY  = 0x5,
    INFO            = 0x6,
    PING            = 0x7,
    ERROR_CHECK     = 0x8
};

using addr_field = limited_value<uint8_t, 3>;
using cmd_field  = limited_value<uint8_t, 15>;
using crc_field  = limited_value<uint8_t, 255>;

class frame {
private:
    uint64_t _field;

public:
    inline uint8_t addr() const { return READFROM(_field, 0, 2); }
    inline uint8_t cmd() const { return READFROM(_field, 2, 4); }
    inline uint64_t parameter() const { return READFROM(_field, 6, 50); }
    inline uint8_t crc() const { return READFROM(_field, 56, 8); }

    inline void set_addr(addr_field a) { WRITETO(_field, 0, 2, static_cast<uint8_t>(a)); }
    inline void set_cmd(cmd_field c) { WRITETO(_field, 2, 4, static_cast<uint8_t>(c)); }
    inline void set_parameter(uint64_t p) { WRITETO(_field, 6, 50, p); }
    inline void set_crc(crc_field c) { WRITETO(_field, 56, 8, static_cast<uint8_t>(c)); }
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
