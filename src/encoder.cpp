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

frame encode_rotate(address addr, int16_t rotate_arg) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::ROTATE);
    f.set_parameter(static_cast<uint64_t>(rotate_arg));
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_stop_normal(address addr) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::STOP_NORMAL);
    f.set_parameter(0);
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

frame encode_stop_emergency(address addr) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(command::STOP_EMERGENCY);
    f.set_parameter(0);
    uint8_t crc = calculate_crc8_atm(f.payload(), 56);
    f.set_crc(crc);
    return f;
}

} // namespace encoder
} // namespace prain_uart
