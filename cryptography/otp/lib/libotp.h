#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>

const size_t MESS_SIZE = 5000;
using ubyte = unsigned char;

class Generator {
protected:
	std::vector<ubyte> key = std::vector<ubyte>(MESS_SIZE);
public:
	Generator();
	virtual void encdec() = 0;
	virtual ~Generator() {};
};

class RawPointerOtp : Generator {
	ubyte* mess;
public:
	RawPointerOtp(const std::string& message);
	void encdec() override;
	const decltype(mess)& message() const;
	~RawPointerOtp();
};

class VectorOtp : Generator {
protected:
	using Generator::key;
	std::vector<ubyte> mess=std::vector<ubyte>(MESS_SIZE);
public:
	VectorOtp(const std::string& message);
	void encdec() override;
	const decltype(mess)& message() const;
	virtual ~VectorOtp() {};
};

class IteratorOtp : VectorOtp {
public:
	IteratorOtp(const std::string& message);
	void encdec() override;
	const decltype(mess)& message() const;
};
