#pragma once

#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {
namespace encoder {

frame encode_move(address addr, uint16_t move_arg);

frame encode_reverse(address addr, uint16_t reverse_arg);

frame encode_turn(address addr, int16_t turn_arg);

frame encode_rotate(address addr, int16_t rotate_arg);

frame encode_stop_normal(address addr);

frame encode_stop_emergency(address addr);

} // namespace encoder
} // namespace prain_uart
