#include <iostream>
#include "../include/prain_uart/protocol.hpp"
#include "../include/prain_uart/encoder.hpp"
#include "../include/prain_uart/decoder.hpp"

int main() {

	prain_uart::frame test = prain_uart::encoder::encode_turn(prain_uart::address::RASPBERRY_HAT, -420);
	auto t1 = test.addr();
	auto t2 = test.cmd();
	auto t3 = test.parameter();
	auto t4 = test.crc();

	prain_uart::decoder dec(test.raw());
	auto d1 = dec.get_address();
	auto d2 = dec.get_command();
	auto d3 = dec.get_raw_parameters();
	auto d4 = dec.get_crc();
	auto d5 = dec.decode_parameters();
	auto d6 = dec.verify_crc();

	auto nparams = dec.get_params<prain_uart::turn_params>();

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
