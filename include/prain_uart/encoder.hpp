#pragma once

#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {
namespace encoder {

frame encode_move(address addr, uint16_t distance);

frame encode_reverse(address addr, uint16_t distance);

frame encode_turn(address addr, int16_t degree);

frame encode_stop(address addr);

frame encode_info(address addr, uint8_t flags);
frame encode_info(address addr, info_flag flag);

frame encode_ping(address addr, uint8_t id);

frame encode_pong(address addr, uint8_t id);

frame encode_error(address addr, uint16_t error_code);
frame encode_error(address addr, error_code code);

frame encode_poll(address addr, uint8_t poll_id);
frame encode_poll(address addr, poll_id id);

frame encode_response(address addr, uint8_t poll_id, uint16_t data);
frame encode_response(address addr, poll_id id, uint16_t data);

frame encode_crane(address addr, uint8_t flag);
frame encode_crane(address addr, crane_flag flag);

} // namespace encoder
} // namespace prain_uart
