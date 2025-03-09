#include "prain_uart/decoder.hpp"

namespace prain_uart {
namespace decoder {

decoded_frame decode(uint64_t raw_frame) {
    decoded_frame result;

    result.addr = static_cast<address>(READFROM(raw_frame, 0, ADDR_SIZE_BITS));
    result.cmd  = static_cast<command>(READFROM(raw_frame, ADDR_SIZE_BITS, CMD_SIZE_BITS));

    uint64_t parameter = READFROM(raw_frame, ADDR_SIZE_BITS + CMD_SIZE_BITS, PARAM_SIZE_BITS);
    uint8_t crc_read   = READFROM(raw_frame, PAYLOAD_SIZE_BITS, CRC_SIZE_BITS);

    uint64_t payload = raw_frame & (((uint64_t)1 << (PAYLOAD_SIZE_BITS)) - 1);
    uint8_t crc_calc = calculate_crc8_atm(payload, PAYLOAD_SIZE_BITS);
    result.crc_ok = (crc_calc == crc_read);

    switch(result.cmd) {
        case command::MOVE:
        case command::REVERSE:
        case command::TURN:
        case command::ROTATE:
            result.arg = static_cast<uint16_t>(parameter & 0xFFFF);
            result.has_arg = true;
            break;
        default:
            result.arg = 0;
            result.has_arg = false;
            break;
    }

    return result;
}

} // namespace decoder
} // namespace prain_uart
