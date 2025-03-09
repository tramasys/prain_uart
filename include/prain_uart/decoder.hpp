#pragma once

#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"
#include <cstdint>

namespace prain_uart {
namespace decoder {

struct decoded_frame {
    address addr;
    command cmd;
    uint16_t arg;
    bool has_arg;
    bool crc_ok;
};

decoded_frame decode(uint64_t raw_frame);

} // namespace decoder
} // namespace prain_uart
