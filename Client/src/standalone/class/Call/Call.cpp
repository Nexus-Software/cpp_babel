#include <iostream>
#include "Call.hpp"

babel::Call::Call()
{
	std::cout << "Call created" << std::endl;
}

babel::Call::~Call()
{
	std::cout << "Call destructed" << std::endl;
}