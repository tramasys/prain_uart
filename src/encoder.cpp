#include "pren_uart/encoder.hpp"

namespace pren_uart {

void encoder::encode(const frame &f, uint8_t out[8])
{
    for (int i = 0; i < 8; ++i) {
        out[i] = 0x00;
    }
}

} // namespace pren_uart
