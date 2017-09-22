#include "BabelClientManager.hpp"

int main(int argc, char *argv[])
{
	babel::BabelClientManager babel;
	
	std::cout << babel.run() << std::endl;
	return 0;
}
