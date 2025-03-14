#include "prain_uart/decoder.hpp"

namespace prain_uart {

decoder::decoder(const frame& f) : frame_(f) {}
decoder::decoder(uint64_t raw_frame) : frame_() { frame_.set_raw(raw_frame); }

address decoder::get_address() const { return static_cast<address>(frame_.addr()); }
command decoder::get_command() const { return static_cast<command>(frame_.cmd()); }
uint64_t decoder::get_raw_parameters() const { return frame_.parameter(); }
uint8_t decoder::get_crc() const { return frame_.crc(); }

decoder::params_variant decoder::decode_parameters() const {
    switch (get_command()) {
        case command::MOVE:     return decode<move_params>();
        case command::REVERSE:  return decode<reverse_params>();
        case command::TURN:     return decode<turn_params>();
        case command::STOP:     return empty_params{};
        case command::INFO:     return decode<info_params>();
        case command::PING:     return decode<ping_params>();
        case command::PONG:     return decode<pong_params>();
        case command::ERROR:    return decode<error_params>();
        case command::POLL:     return decode<poll_params>();
        case command::RESPONSE: return decode<response_params>();
        case command::CRANE:    return decode<crane_params>();
        default: throw std::runtime_error("Unknown command");
    }
}

bool decoder::verify_crc() const {
    return calculate_crc8_atm(frame_.payload(), PAYLOAD_SIZE_BITS) == frame_.crc();
}

template <typename T>
T decoder::decode() const {
    auto param = frame_.parameter();

    if constexpr (std::is_same_v<T, move_params>) {
        return { static_cast<uint16_t>(param) };
    } else if constexpr (std::is_same_v<T, reverse_params>) {
        return { static_cast<uint16_t>(param) };
    } else if constexpr (std::is_same_v<T, turn_params>) {
        return { static_cast<int16_t>(param) };
    } else if constexpr (std::is_same_v<T, info_params>) {
        return { static_cast<uint8_t>(param) };
    } else if constexpr (std::is_same_v<T, error_params>) {
        return { static_cast<uint16_t>(param) };
    } else if constexpr (std::is_same_v<T, ping_params>) {
        return { static_cast<uint8_t>(param) };
    } else if constexpr (std::is_same_v<T, pong_params>) {
        return { static_cast<uint8_t>(param) };
    } else if constexpr (std::is_same_v<T, poll_params>) {
        return { static_cast<uint8_t>(param) };
    } else if constexpr (std::is_same_v<T, response_params>) {
        return { static_cast<uint8_t>(param), static_cast<uint16_t>(param >> 8) };
    } else if constexpr (std::is_same_v<T, crane_params>) {
        return { static_cast<uint8_t>(param) };
    } else if constexpr (std::is_same_v<T, rotate_params>) {
        return { static_cast<int16_t>(param) };
    }

    return {};
}

} // namespace prain_uart
