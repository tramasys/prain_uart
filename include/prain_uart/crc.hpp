#pragma once
#include <cstddef>
#include <cstdint>

namespace prain_uart {

// Computes CRC8-ATM over the most-significant 'bit_length' bits of data.
uint8_t calculate_crc8_atm(uint64_t data, std::size_t bit_length);

} // namespace prain_uart
