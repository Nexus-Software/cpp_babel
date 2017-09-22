#include "BabelClientManager.hpp"

int main(int argc, char *argv[])
{
	babel::BabelClientManager babel;
	
	std::cout << babel.run() << std::endl;
	try {
		std::cout << babel.getContact().getContactByLogin("herbaux").getStatus() << std::endl;
	}
	catch (babel::ContactException& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
