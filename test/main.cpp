#include <iostream>
#include "../include/prain_uart/protocol.hpp"
#include "../include/prain_uart/encoder.hpp"
#include "../include/prain_uart/decoder.hpp"

int main() {

	prain_uart::frame pytest;
	// move 100 to motion ctrl
	pytest.set_raw(0b1110110100000000000000000000000000000000000000000001100100000001);

	prain_uart::decoder dec1(pytest);
	auto a1 = dec1.get_address();
	auto c1 = dec1.get_command();
	auto crc1 = dec1.get_crc();
	auto raw_params1 = dec1.get_raw_parameters();
	auto nparams1 = dec1.get_params<prain_uart::move_params>();

	prain_uart::frame bbb = prain_uart::encoder::encode_response(
		prain_uart::address::RASPBERRY_HAT,
		prain_uart::poll_id::DISTANCE,
		420
	);

	prain_uart::decoder dec_bbb(bbb.raw());
	auto naddr_bbb = dec_bbb.get_address();
	auto ncmd_bbb = dec_bbb.get_command();
	auto crc_bbb = dec_bbb.verify_crc();
	auto nraw_bbb = dec_bbb.get_raw_parameters();
	auto nparams_bbb = dec_bbb.get_params<prain_uart::response_params>();

	prain_uart::frame test = prain_uart::encoder::encode_turn(
		prain_uart::address::RASPBERRY_HAT,
		-420
	);

	auto t1 = test.addr();
	auto t2 = test.cmd();
	auto t3 = test.parameter();
	auto t4 = test.crc();

	prain_uart::frame a;

	uint8_t b = 0;
	a.set_addr(prain_uart::address::RASPBERRY_HAT);
	b = a.addr();
	a.set_addr(prain_uart::address::MOTION_CTRL);
	b = a.addr();
	a.set_addr(prain_uart::address::GRIP_CTRL);
	b = a.addr();

	a.set_addr(0b11);
	a.set_cmd(0b0100);
	a.set_parameter(0b10000000000000000000000000000000000000000000000001);
	a.set_crc(0b11111111);

	auto addr = a.addr();
	auto cmd = a.cmd();
	auto param = a.parameter();
	auto crc = a.crc();

	std::cout << "addr: " << addr << "\n";
	std::cout << "cmd: " << cmd << "\n";
	std::cout << "param: " << param << "\n";
	std::cout << "addr: " << crc << "\n";

	return 0;
}
