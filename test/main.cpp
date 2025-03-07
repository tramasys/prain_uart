#include <iostream>
#include "../include/prain_uart/protocol.hpp"

int main() {
	prain_uart::frame a;

	uint8_t b;
	a.set_addr(prain_uart::address::RASPBERRY_HAT);
	b = a.addr();
	a.set_addr(prain_uart::address::MOTION_CTRL);
	b = a.addr();
	a.set_addr(prain_uart::address::GRIP_CTRL);
	b = a.addr();

	a.set_addr(0b00);
	a.set_cmd(0b0000);
	a.set_parameter(0b11111111111111111111111111111111111111111111111111);
	a.set_crc(0b00000000);

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
