#include <iostream>
#include "../include/prain_uart/protocol.hpp"
#include "../include/prain_uart/encoder.hpp"
#include "../include/prain_uart/decoder.hpp"

int main() {

	prain_uart::frame test = prain_uart::encoder::encode_reverse(prain_uart::address::RASPBERRY_HAT, 420);
	auto t1 = test.addr();
	auto t2 = test.cmd();
	auto t3 = test.parameter();
	auto t4 = test.crc();

	auto sss = test.raw();
	prain_uart::decoder::decoded_frame test2 = prain_uart::decoder::decode(sss);
	auto t5 = test2.addr;
	auto t6 = test2.cmd;
	auto t7 = test2.arg;
	auto t8 = test2.has_arg;
	auto t9 = test2.crc_ok;

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
