#include "prain_uart/decoder.hpp" // For params structs
#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {
namespace encoder {

template <typename Params>
frame encode(address addr, command cmd, const Params& params) {
    frame f;
    f.set_addr(addr);
    f.set_cmd(cmd);

    if constexpr (std::is_same_v<Params, empty_params>) {
        f.set_parameter(0);
    } else if constexpr (std::is_same_v<Params, response_params>) {
        f.set_parameter((static_cast<uint64_t>(params.data) << 8) | params.poll_id);
    } else if constexpr (std::is_same_v<Params, move_params>) {
        f.set_parameter(static_cast<uint64_t>(params.distance));
    } else if constexpr (std::is_same_v<Params, reverse_params>) {
        f.set_parameter(static_cast<uint64_t>(params.distance));
    } else if constexpr (std::is_same_v<Params, turn_params>) {
        f.set_parameter(static_cast<uint64_t>(params.angle));
    } else if constexpr (std::is_same_v<Params, rotate_params>) {
        f.set_parameter(static_cast<uint64_t>(params.angle));
    } else if constexpr (std::is_same_v<Params, info_params>) {
        f.set_parameter(static_cast<uint64_t>(params.flag));
    } else if constexpr (std::is_same_v<Params, ping_params>) {
        f.set_parameter(static_cast<uint64_t>(params.id));
    } else if constexpr (std::is_same_v<Params, pong_params>) {
        f.set_parameter(static_cast<uint64_t>(params.id));
    } else if constexpr (std::is_same_v<Params, error_params>) {
        f.set_parameter(static_cast<uint64_t>(params.error_code));
    } else if constexpr (std::is_same_v<Params, poll_params>) {
        f.set_parameter(static_cast<uint64_t>(params.poll_id));
    } else if constexpr (std::is_same_v<Params, crane_params>) {
        f.set_parameter(static_cast<uint64_t>(params.flag));
    }

    f.set_crc(calculate_crc8_atm(f.payload(), PAYLOAD_SIZE_BITS));
    return f;
}

frame encode_move(address addr, uint16_t distance) {
    return encode(addr, command::MOVE, move_params{distance});
}

frame encode_reverse(address addr, uint16_t distance) {
    return encode(addr, command::REVERSE, reverse_params{distance});
}

frame encode_turn(address addr, int16_t degree) {
    return encode(addr, command::TURN, turn_params{degree});
}

frame encode_stop(address addr) {
    return encode(addr, command::STOP, empty_params{});
}

frame encode_info(address addr, uint8_t flags) {
    return encode(addr, command::INFO, info_params{flags});
}

frame encode_info(address addr, info_flag flag) {
    return encode_info(addr, static_cast<uint8_t>(flag));
}

frame encode_ping(address addr, uint8_t id) {
    return encode(addr, command::PING, ping_params{id});
}

frame encode_pong(address addr, uint8_t id) {
    return encode(addr, command::PONG, pong_params{id});
}

frame encode_error(address addr, uint16_t error_code) {
    return encode(addr, command::ERROR, error_params{error_code});
}

frame encode_error(address addr, error_code code) {
    return encode_error(addr, static_cast<uint16_t>(code));
}

frame encode_poll(address addr, uint8_t poll_id) {
    return encode(addr, command::POLL, poll_params{poll_id});
}

frame encode_poll(address addr, poll_id id) {
    return encode_poll(addr, static_cast<uint8_t>(id));
}

frame encode_response(address addr, uint8_t poll_id, uint16_t data) {
    return encode(addr, command::RESPONSE, response_params{poll_id, data});
}

frame encode_response(address addr, poll_id id, uint16_t data) {
    return encode_response(addr, static_cast<uint8_t>(id), data);
}

frame encode_crane(address addr, uint8_t flag) {
    return encode(addr, command::CRANE, crane_params{flag});
}

frame encode_crane(address addr, crane_flag flag) {
    return encode_crane(addr, static_cast<uint8_t>(flag));
}

} // namespace encoder
} // namespace prain_uart
