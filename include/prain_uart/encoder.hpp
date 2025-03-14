#pragma once

#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {
namespace encoder {

frame encode_move(address addr, uint16_t move_arg);

frame encode_reverse(address addr, uint16_t reverse_arg);

frame encode_turn(address addr, int16_t turn_arg);

frame encode_stop(address addr);

frame encode_info(address addr, uint8_t flags);

frame encode_ping(address addr, uint8_t id);

frame encode_pong(address addr, uint8_t id);

frame encode_error(address addr, uint16_t error_code);

frame encode_poll(address addr, uint8_t poll_id);

frame encode_rsp(address addr, uint8_t poll_id, uint16_t data);

frame encode_crane(address addr, uint8_t flag);

} // namespace encoder
} // namespace prain_uart
