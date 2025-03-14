#include "prain_uart/encoder.hpp"

namespace prain_uart {
namespace encoder {

frame encode_move(address addr, uint16_t distance) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::MOVE);
    f.set_parameter(static_cast<uint64_t>(distance));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_reverse(address addr, uint16_t distance) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::REVERSE);
    f.set_parameter(static_cast<uint64_t>(distance));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_turn(address addr, int16_t degree) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::TURN);
    f.set_parameter(static_cast<uint64_t>(degree));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_stop(address addr) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::STOP);
    f.set_parameter(0);
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_info(address addr, uint8_t flags) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::INFO);
    f.set_parameter(static_cast<uint64_t>(flags));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_info(address addr, info_flag flag) {
    return encode_info(addr, static_cast<uint8_t>(flag));
}

frame encode_ping(address addr, uint8_t id) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::PING);
    f.set_parameter(static_cast<uint64_t>(id));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_pong(address addr, uint8_t id) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::PONG);
    f.set_parameter(static_cast<uint64_t>(id));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_error(address addr, uint16_t error_code) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::ERROR);
    f.set_parameter(static_cast<uint64_t>(error_code));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_error(address addr, error_code code) {
    return encode_error(addr, static_cast<uint16_t>(code));
}

frame encode_poll(address addr, uint8_t poll_id) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::POLL);
    f.set_parameter(static_cast<uint64_t>(poll_id));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_poll(address addr, poll_id id) {
    return encode_poll(addr, static_cast<uint8_t>(id));
}

frame encode_response(address addr, uint8_t poll_id, uint16_t data) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::RESPONSE);
    f.set_parameter(static_cast<uint64_t>(poll_id) << 16 | data);
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_response(address addr, poll_id id, uint16_t data) {
    return encode_response(addr, static_cast<uint8_t>(id), data);
}

frame encode_crane(address addr, uint8_t flag) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::CRANE);
    f.set_parameter(static_cast<uint64_t>(flag));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_crane(address addr, crane_flag flag) {
    return encode_crane(addr, static_cast<uint8_t>(flag));
}

} // namespace encoder
} // namespace prain_uart
