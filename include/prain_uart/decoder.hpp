#pragma once

#include <cstdint>
#include "protocol.hpp"

namespace prain_uart {

class decoder
{
public:
    decoder() = default;
    ~decoder() = default;

    frame decode(const uint8_t raw[8]);
};

} // namespace prain_uart
