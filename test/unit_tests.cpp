#include <gtest/gtest.h>
#include "../include/prain_uart/encoder.hpp"
#include "../include/prain_uart/decoder.hpp"
#include "../include/prain_uart/crc.hpp"

class PrainUartTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PrainUartTest, MoveRoundTrip) {
    prain_uart::frame f = prain_uart::encoder::encode_move(
        prain_uart::address::RASPBERRY_HAT,
        1234
    );
    prain_uart::decoder dec(f.raw());

    EXPECT_EQ(dec.get_address(), prain_uart::address::RASPBERRY_HAT);
    EXPECT_EQ(dec.get_command(), prain_uart::command::MOVE);
    EXPECT_TRUE(dec.verify_crc());
    EXPECT_EQ(dec.get_raw_parameters(), 1234);

    auto params = dec.get_params<prain_uart::move_params>();
    EXPECT_EQ(params.distance, 1234);
}

TEST_F(PrainUartTest, ResponseRoundTrip) {
    prain_uart::frame f = prain_uart::encoder::encode_response(
        prain_uart::address::MOTION_CTRL,
        prain_uart::poll_id::DISTANCE,
        420
    );
    prain_uart::decoder dec(f.raw());

    EXPECT_EQ(dec.get_address(), prain_uart::address::MOTION_CTRL);
    EXPECT_EQ(dec.get_command(), prain_uart::command::RESPONSE);
    EXPECT_TRUE(dec.verify_crc());

    auto params = dec.get_params<prain_uart::response_params>();
    EXPECT_EQ(params.poll_id, static_cast<uint8_t>(prain_uart::poll_id::DISTANCE));
    EXPECT_EQ(params.data, 420);
}

TEST_F(PrainUartTest, StopRoundTrip) {
    prain_uart::frame f = prain_uart::encoder::encode_stop(
        prain_uart::address::GRIP_CTRL
    );
    prain_uart::decoder dec(f.raw());

    EXPECT_EQ(dec.get_address(), prain_uart::address::GRIP_CTRL);
    EXPECT_EQ(dec.get_command(), prain_uart::command::STOP);
    EXPECT_TRUE(dec.verify_crc());
    EXPECT_EQ(dec.get_raw_parameters(), 0);

    EXPECT_NO_THROW(dec.get_params<prain_uart::empty_params>());
}

TEST_F(PrainUartTest, TypeMismatchThrows) {
    prain_uart::frame f = prain_uart::encoder::encode_move(
        prain_uart::address::RASPBERRY_HAT,
        5678
    );
    prain_uart::decoder dec(f.raw());

    EXPECT_THROW(
        dec.get_params<prain_uart::response_params>(),
        std::runtime_error
    );
}

TEST_F(PrainUartTest, InvalidCrc) {
    prain_uart::frame f = prain_uart::encoder::encode_ping(
        prain_uart::address::MOTION_CTRL,
        42
    );
    uint64_t raw = f.raw();
    raw ^= 0xFFULL << 56; // Flip CRC bits
    prain_uart::decoder dec(raw);

    EXPECT_FALSE(dec.verify_crc());
}

TEST_F(PrainUartTest, UnknownCommandThrows) {
    prain_uart::frame f;
    f.set_addr(prain_uart::address::RASPBERRY_HAT);
    f.set_cmd(prain_uart::cmd_field(0xF)); // Invalid command (15)
    f.set_parameter(0);
    f.set_crc(prain_uart::calculate_crc8_atm(f.payload(), prain_uart::PAYLOAD_SIZE_BITS));

    prain_uart::decoder dec(f.raw());
    EXPECT_THROW(
        dec.get_params<prain_uart::empty_params>(),
        std::runtime_error
    );
}
