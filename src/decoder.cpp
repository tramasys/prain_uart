#include "prain_uart/decoder.hpp"

namespace prain_uart {

decoder::decoder(const frame& f) : frame_data_(f.raw()) {}

decoder::decoder(uint64_t raw_frame) : frame_data_(raw_frame) {}

address decoder::get_address() const {
    return static_cast<address>(extract_addr());
}

command decoder::get_command() const {
    return static_cast<command>(extract_cmd());
}

uint64_t decoder::get_raw_parameters() const {
    return extract_parameter();
}

uint8_t decoder::get_crc() const {
    return extract_crc();
}

decoder::params_variant decoder::decode_parameters() const {
    switch (get_command()) {
        case command::MOVE:
            return decode_move();
        case command::REVERSE:
            return decode_reverse();
        case command::TURN:
            return decode_turn();
        case command::ROTATE:
            return decode_rotate();
        case command::STOP_NORMAL:
        case command::STOP_EMERGENCY:
        case command::PING:
            return empty_params{};
        case command::INFO:
            return decode_info();
        case command::ERROR_CHECK:
            return decode_error_check();
        default:
            throw std::runtime_error("unknown command");
    }
}

bool decoder::verify_crc() const {
    uint64_t payload = extract_payload();
    uint8_t calculated_crc = calculate_crc8_atm(payload, PAYLOAD_SIZE_BITS);
    return calculated_crc == extract_crc();
}

move_params decoder::decode_move() const {
    uint64_t param = extract_parameter();
    return move_params{static_cast<uint16_t>(param & 0xffff)};
}

reverse_params decoder::decode_reverse() const {
    uint64_t param = extract_parameter();
    return reverse_params{static_cast<uint16_t>(param & 0xffff)};
}

turn_params decoder::decode_turn() const {
    uint64_t param = extract_parameter();
    return turn_params{static_cast<int16_t>(param & 0xffff)};
}

rotate_params decoder::decode_rotate() const {
    uint64_t param = extract_parameter();
    return rotate_params{static_cast<int16_t>(param & 0xffff)};
}

info_params decoder::decode_info() const {
    uint64_t param = extract_parameter();
    return info_params{
        static_cast<uint8_t>((param >> 24) & 0xff),
        static_cast<uint8_t>((param >> 16) & 0xff),
        static_cast<uint8_t>((param >> 8) & 0xff),
        static_cast<uint8_t>(param & 0xff)
    };
}

error_check_params decoder::decode_error_check() const {
    uint64_t param = extract_parameter();
    return error_check_params{static_cast<uint16_t>(param & 0xffff)};
}

uint8_t decoder::extract_addr() const {
    return READFROM(frame_data_, 0, ADDR_SIZE_BITS);
}

uint8_t decoder::extract_cmd() const {
    return READFROM(frame_data_, ADDR_SIZE_BITS, CMD_SIZE_BITS);
}

uint64_t decoder::extract_parameter() const {
    return READFROM(frame_data_, ADDR_SIZE_BITS + CMD_SIZE_BITS, PARAM_SIZE_BITS);
}

uint8_t decoder::extract_crc() const {
    return READFROM(frame_data_, PAYLOAD_SIZE_BITS, CRC_SIZE_BITS);
}

uint64_t decoder::extract_payload() const {
    return READFROM(frame_data_, 0, PAYLOAD_SIZE_BITS);
}

} // namespace prain_uart
