#pragma once
#include <iostream>

class Numeric
{
public:
	Numeric();
	~Numeric();

	static bool IsDigit(const char* data, std::size_t size);
};