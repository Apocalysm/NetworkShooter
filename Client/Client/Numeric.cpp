#include "Numeric.h"

// Checks if the recieved string is using acceptable characters for an ip-address
bool Numeric::IsDigit(const char* data, std::size_t size)
{
	for (std::size_t i = 0; i < size; i++)
	{
		if (data[i] == '0')
			return true;
		else if (data[i] == '1')
			return true;
		else if (data[i] == '2')
			return true;
		else if (data[i] == '3')
			return true;
		else if (data[i] == '4')
			return true;
		else if (data[i] == '5')
			return true;
		else if (data[i] == '6')
			return true;
		else if (data[i] == '7')
			return true;
		else if (data[i] == '8')
			return true;
		else if (data[i] == '9')
			return true;
		else if (data[i] == '.')
			return true;
		else
			return false;
	}
}
