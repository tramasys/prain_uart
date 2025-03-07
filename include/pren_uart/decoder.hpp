#pragma once

#include <cstdint>
#include "protocol.hpp"

namespace pren_uart {

class decoder
{
public:
    decoder() = default;
    ~decoder() = default;

    frame decode(const uint8_t raw[8]);
};

} // namespace pren_uart
