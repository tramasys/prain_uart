#pragma once

#include <cstdint>
#include "protocol.hpp"

namespace pren_uart {

class encoder
{
public:
    encoder() = default;
    ~encoder() = default;

    void encode(const frame &f, uint8_t out[8]);
};

} // namespace pren_uart
