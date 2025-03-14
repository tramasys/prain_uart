#pragma once

#include <variant>
#include <stdexcept>
#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {

struct move_params {
    uint16_t distance;
};

struct reverse_params {
    uint16_t distance;
};

struct turn_params {
    int16_t angle;
};

struct rotate_params {
    int16_t angle;
};

struct info_params {
    uint8_t flag;
};

struct error_params {
    uint16_t error_code;
};

struct ping_params {
    uint8_t id;
};

struct pong_params {
    uint8_t id;
};

struct poll_params {
    uint8_t poll_id;
};

struct response_params {
    uint8_t  poll_id;
    uint16_t data;
};

struct crane_params {
    uint8_t flag;
};

struct empty_params {};

class decoder {
public:
    using params_variant = std::variant<
        move_params,
        reverse_params,
        turn_params,
        rotate_params,
        info_params,
        empty_params,
        error_params,
        ping_params,
        pong_params,
        poll_params,
        response_params,
        crane_params
    >;

    explicit decoder(const frame& f);
    explicit decoder(uint64_t raw_frame);

    address get_address() const;
    command get_command() const;
    uint64_t get_raw_parameters() const;
    uint8_t get_crc() const;
    params_variant decode_parameters() const;
    bool verify_crc() const;

    template <typename T>
    T get_params() const {
        auto params = decode_parameters();
        if (auto* p = std::get_if<T>(&params))
            return *p;
        throw std::runtime_error("Decoded parameter type mismatch");
    }

private:
    uint64_t frame_data_;

    move_params     decode_move() const;
    reverse_params  decode_reverse() const;
    turn_params     decode_turn() const;
    info_params     decode_info() const;
    error_params    decode_error() const;
    ping_params     decode_ping() const;
    pong_params     decode_pong() const;
    poll_params     decode_poll() const;
    response_params decode_response() const;
    crane_params    decode_crane() const;

    uint8_t  extract_addr() const;
    uint8_t  extract_cmd() const;
    uint64_t extract_parameter() const;
    uint8_t  extract_crc() const;
    uint64_t extract_payload() const;
};

} // namespace prain_uart
