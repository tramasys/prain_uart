#pragma once

#include <variant>
#include "prain_uart/protocol.hpp"
#include "prain_uart/crc.hpp"

namespace prain_uart {

struct move_params      { uint16_t distance; };
struct reverse_params   { uint16_t distance; };
struct turn_params      { int16_t angle; };
struct rotate_params    { int16_t angle; };
struct info_params      { uint8_t flag; };
struct error_params     { uint16_t error_code; };
struct ping_params      { uint8_t id; };
struct pong_params      { uint8_t id; };
struct poll_params      { uint8_t poll_id; };
struct response_params  { uint8_t poll_id; uint16_t data; };
struct empty_params     {};

class decoder {
public:
    using params_variant = std::variant<
        move_params, reverse_params, turn_params, rotate_params,
        info_params, empty_params, error_params, ping_params,
        pong_params, poll_params, response_params
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
        if (auto* p = std::get_if<T>(&params)) return *p;
        return T{};
    }

private:
    frame frame_;

    template <typename T>
    T decode() const;
};

} // namespace prain_uart
