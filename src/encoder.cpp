#include "prain_uart/encoder.hpp"

namespace prain_uart {
namespace encoder {

frame encode_move(address addr, uint16_t move_arg) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::MOVE);
    f.set_parameter(static_cast<uint64_t>(move_arg));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_reverse(address addr, uint16_t reverse_arg) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::REVERSE);
    f.set_parameter(static_cast<uint64_t>(reverse_arg));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_turn(address addr, int16_t turn_arg) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::TURN);
    f.set_parameter(static_cast<uint64_t>(turn_arg));
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

frame encode_poll(address addr, uint8_t poll_id) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::POLL);
    f.set_parameter(static_cast<uint64_t>(poll_id));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_rsp(address addr, uint8_t poll_id, uint16_t data) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::RSP);
    f.set_parameter(static_cast<uint64_t>(poll_id) << 16 | data);
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
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

} // namespace encoder
} // namespace prain_uart
