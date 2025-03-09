#include "prain_uart/crc.hpp"

namespace prain_uart {

uint8_t calculate_crc8_atm(uint64_t data, std::size_t bit_length) {
    uint8_t crc = 0;
    for (std::size_t i = 0; i < bit_length; ++i) {
        // Process bit-by-bit (MSB first)
        bool bit = ((data >> (bit_length - 1 - i)) & 1) ^ ((crc >> 7) & 1);
        crc <<= 1;
        if (bit)
            crc ^= 0x07; // CRC8-ATM polynomial: x^8 + x^2 + x + 1 (0x07)
    }
    return crc;
}

} // namespace prain_uart
