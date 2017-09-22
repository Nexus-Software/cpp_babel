#include <iostream>
#include "Contact.hpp"

babel::Contact::Contact()
{
	std::cout << "Contact created" << std::endl;
}

babel::Contact::~Contact()
{
	std::cout << "Contact destructed" << std::endl;
}