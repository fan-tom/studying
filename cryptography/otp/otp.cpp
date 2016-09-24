#include <iostream>
#include <fstream>
#include "lib\libotp.h"

void main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please, specify path to file" << std::endl;
		std::exit(1);
	}
	std::cout << argv[1] << std::endl;
	auto file = std::ifstream(argv[1], std::ios::in|std::ios::binary);
	if (!file) {
		std::cout << "Cannot open file" << argv[1] << std::endl;
		std::exit(2);
	}
	std::string message;
	message.reserve(MESS_SIZE);
	std::istreambuf_iterator<char> iter(file), end;
	message.assign(iter, end);
	message[message.size() - 1] = 0;
	std::cout << "Message:" << message << std::endl;
	
	auto rpotp = RawPointerOtp(message);
	rpotp.encdec();
	rpotp.encdec();
	if (std::equal(message.cbegin(), message.cend(), rpotp.message(), rpotp.message() + MESS_SIZE))
		std::cout << "Raw pointer class comparison succeeded" << std::endl;

	auto votp = VectorOtp(message);
	votp.encdec();
	votp.encdec();
	if (std::equal(message.cbegin(), message.cend(), votp.message().cbegin(), votp.message().cend()))
		std::cout << "Vector class comparison succeeded" << std::endl;

	auto iterotp = IteratorOtp(message);
	iterotp.encdec();
	iterotp.encdec();
	if (std::equal(message.cbegin(), message.cend(), iterotp.message().cbegin(), iterotp.message().cend()))
		std::cout << "Iterator class comparison succeeded" << std::endl;
}
