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

    auto params = dec.get_params<prain_uart::move_params>();
    EXPECT_EQ(params.distance, 1234);
}

TEST_F(PrainUartTest, ReverseRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_reverse(
		prain_uart::address::MOTION_CTRL,
		5678
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::MOTION_CTRL);
	EXPECT_EQ(dec.get_command(), prain_uart::command::REVERSE);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::reverse_params>();
	EXPECT_EQ(params.distance, 5678);
}

TEST_F(PrainUartTest, TurnRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_turn(
		prain_uart::address::GRIP_CTRL,
		-420
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::GRIP_CTRL);
	EXPECT_EQ(dec.get_command(), prain_uart::command::TURN);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::turn_params>();
	EXPECT_EQ(params.angle, -420);
}

TEST_F(PrainUartTest, StopRoundTrip) {
    prain_uart::frame f = prain_uart::encoder::encode_stop(
        prain_uart::address::GRIP_CTRL
    );
    prain_uart::decoder dec(f.raw());

    EXPECT_EQ(dec.get_address(), prain_uart::address::GRIP_CTRL);
    EXPECT_EQ(dec.get_command(), prain_uart::command::STOP);
    EXPECT_TRUE(dec.verify_crc());

    EXPECT_NO_THROW(dec.get_params<prain_uart::empty_params>());
}

TEST_F(PrainUartTest, InfoRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_info(
		prain_uart::address::RASPBERRY_HAT,
		static_cast<uint8_t>(prain_uart::info_flag::BATTERY)
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::RASPBERRY_HAT);
	EXPECT_EQ(dec.get_command(), prain_uart::command::INFO);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::info_params>();
	EXPECT_EQ(params.flag, static_cast<uint8_t>(prain_uart::info_flag::BATTERY));
}

TEST_F(PrainUartTest, PingRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_ping(
		prain_uart::address::MOTION_CTRL,
		42
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::MOTION_CTRL);
	EXPECT_EQ(dec.get_command(), prain_uart::command::PING);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::ping_params>();
	EXPECT_EQ(params.id, 42);
}

TEST_F(PrainUartTest, PongRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_pong(
		prain_uart::address::RASPBERRY_HAT,
		42
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::RASPBERRY_HAT);
	EXPECT_EQ(dec.get_command(), prain_uart::command::PONG);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::pong_params>();
	EXPECT_EQ(params.id, 42);
}

TEST_F(PrainUartTest, ErrorRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_error(
		prain_uart::address::GRIP_CTRL,
		0x1234
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::GRIP_CTRL);
	EXPECT_EQ(dec.get_command(), prain_uart::command::ERROR);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::error_params>();
	EXPECT_EQ(params.error_code, 0x1234);
}

TEST_F(PrainUartTest, PollRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_poll(
		prain_uart::address::MOTION_CTRL,
		static_cast<uint8_t>(prain_uart::poll_id::DEGREE)
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::MOTION_CTRL);
	EXPECT_EQ(dec.get_command(), prain_uart::command::POLL);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::poll_params>();
	EXPECT_EQ(params.poll_id, static_cast<uint8_t>(prain_uart::poll_id::DEGREE));
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

TEST_F(PrainUartTest, CraneRoundTrip) {
	prain_uart::frame f = prain_uart::encoder::encode_crane(
		prain_uart::address::RASPBERRY_HAT,
		static_cast<uint8_t>(prain_uart::crane_flag::UP)
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::RASPBERRY_HAT);
	EXPECT_EQ(dec.get_command(), prain_uart::command::CRANE);
	EXPECT_TRUE(dec.verify_crc());
	EXPECT_EQ(dec.get_raw_parameters(), static_cast<uint8_t>(prain_uart::crane_flag::UP));

	auto params = dec.get_params<prain_uart::crane_params>();
	EXPECT_EQ(params.flag, static_cast<uint8_t>(prain_uart::crane_flag::UP));
}

TEST_F(PrainUartTest, TypeMismatchReturnsEmptyParams) {
    prain_uart::frame f = prain_uart::encoder::encode_move(
        prain_uart::address::RASPBERRY_HAT,
        5678
    );
    prain_uart::decoder dec(f.raw());

	EXPECT_EQ(dec.get_address(), prain_uart::address::RASPBERRY_HAT);
	EXPECT_EQ(dec.get_command(), prain_uart::command::MOVE);
	EXPECT_TRUE(dec.verify_crc());

	auto params = dec.get_params<prain_uart::info_params>();
	EXPECT_EQ(params.flag, 0);
}

TEST_F(PrainUartTest, ValidCrc) {
	prain_uart::frame f = prain_uart::encoder::encode_ping(
		prain_uart::address::MOTION_CTRL,
		42
	);
	prain_uart::decoder dec(f.raw());

	EXPECT_TRUE(dec.verify_crc());
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

TEST_F(PrainUartTest, CrcFromPythonLibIsCorrect) {
	// Encoded in python lib as: frame = encode_move(Address.MOTION_CTRL, 420)
	uint64_t data = 0b100111100000000000000000000000000000000000000000110100100000001;

	prain_uart::frame f;
	f.set_raw(data);

	EXPECT_EQ(f.crc(), 79);
	EXPECT_EQ(prain_uart::calculate_crc8_atm(data, 50), 79);
	EXPECT_EQ(prain_uart::calculate_crc8_atm(data, 50), 0x4f);
	EXPECT_EQ(prain_uart::calculate_crc8_atm(data, 50), f.crc());
}
