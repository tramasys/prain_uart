#pragma once

#include <cstdint>
#include <cstddef>
#include "helper.hpp"

namespace prain_uart {

constexpr std::size_t FRAME_SIZE_BITS = 64;
constexpr std::size_t PAYLOAD_SIZE_BITS = 56;
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
    STOP            = 0x3,
    INFO            = 0x4,
    PING            = 0x5,
    PONG            = 0x6,
    ERROR           = 0x7,
    POLL            = 0x8,
    RESPONSE        = 0x9,
    GRIP            = 0xA,
    RELEASE         = 0xB,
};

enum class info_flag : uint8_t {
    BATTERY         = 0x0,
    TEMPERATURE     = 0x1,
    LOST_LINE       = 0x2,
    NODE_DETECTED   = 0x3,
    BARRIER_DETECTED= 0x4,
    MOTION_DONE     = 0x5,
    // more ...
};

enum class poll_id : uint8_t {
    DEGREE          = 0x0,
    DISTANCE        = 0x1,
    LINE_SENSOR     = 0x2,
    ULTRASONIC      = 0x3,
    // more ...
};

enum class error_code : uint16_t {
    INVALID_CRC     = 0x0,
    INVALID_CMD     = 0x1,
    INTERNAL        = 0x2,
    // more ...
};

using addr_field = limited_value<uint8_t, 3>;
using cmd_field  = limited_value<uint8_t, 15>;
using crc_field  = limited_value<uint8_t, 255>;

struct frame {
private:
    uint64_t _field{0};

public:
    frame() = default;

    inline uint8_t addr() const { return read_from<0, ADDR_SIZE_BITS>(_field); }
    inline uint8_t cmd() const { return read_from<2, CMD_SIZE_BITS>(_field); }
    inline uint64_t parameter() const { return read_from<6, PARAM_SIZE_BITS>(_field); }
    inline uint8_t crc() const { return read_from<56, CRC_SIZE_BITS>(_field); }

    inline void set_addr(addr_field a) { write_to<0, ADDR_SIZE_BITS>(_field, a); }
    inline void set_cmd(cmd_field c) { write_to<2, CMD_SIZE_BITS>(_field, c); }

    // ensure that only the lower 50 bits are set
    inline void set_parameter(uint64_t p) { write_to<6, PARAM_SIZE_BITS>(_field, p & ((uint64_t{1} << PARAM_SIZE_BITS) - 1)); }
    inline void set_crc(crc_field c) { write_to<56, CRC_SIZE_BITS>(_field, c); }

    inline void set_addr(address a) { set_addr(addr_field(static_cast<uint8_t>(a))); }
    inline void set_cmd(command c) { set_cmd(cmd_field(static_cast<uint8_t>(c))); }
    inline void set_crc(uint8_t c) { set_crc(crc_field(c)); }

    inline uint64_t payload() const { return _field & ((uint64_t{1} << PAYLOAD_SIZE_BITS) - 1); }

    inline uint64_t raw() const { return _field; }
    inline void set_raw(uint64_t raw_frame) { _field = raw_frame; }
};

} // namespace prain_uart
