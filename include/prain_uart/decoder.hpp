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
    uint8_t status;
    uint8_t version;
    uint8_t temp;
    uint8_t battery;
};

struct empty_params {};

struct error_check_params {
    uint16_t error_code;
};

class decoder {
public:
    using params_variant = std::variant<
        move_params, reverse_params, turn_params, rotate_params,
        empty_params, info_params, error_check_params
    >;

    explicit decoder(const frame& f);
    explicit decoder(uint64_t raw_frame);

    address get_address() const;
    command get_command() const;
    uint64_t get_raw_parameters() const;
    uint8_t get_crc() const;
    params_variant decode_parameters() const;
    bool verify_crc() const;

    // Template helper: returns the parameter in the expected type
    template <typename T>
    T get_params() const {
        auto params = decode_parameters();
        if (auto* p = std::get_if<T>(&params))
            return *p;
        throw std::runtime_error("Decoded parameter type mismatch");
    }

private:
    uint64_t frame_data_;

    move_params decode_move() const;
    reverse_params decode_reverse() const;
    turn_params decode_turn() const;
    rotate_params decode_rotate() const;
    info_params decode_info() const;
    error_check_params decode_error_check() const;

    uint8_t extract_addr() const;
    uint8_t extract_cmd() const;
    uint64_t extract_parameter() const;
    uint8_t extract_crc() const;
    uint64_t extract_payload() const;
};

} // namespace prain_uart
