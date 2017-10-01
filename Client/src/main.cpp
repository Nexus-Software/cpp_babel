#include "BabelClientManager.hpp"

int main(int argc, char **argv)
{
	try {
		babel::BabelClientManager babel(argc, argv);
		return babel.run();
	}
	catch (...) {
		return (0);
	}
	
}
