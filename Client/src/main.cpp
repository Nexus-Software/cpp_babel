#include "BabelClientManager.hpp"

int main(int argc, char **argv)
{
	babel::BabelClientManager babel(argc, argv);

	// babel.getMedia().setAudioStreamState(true);
	// while (1)
	// 	babel.getMedia().playSound(babel.getMedia().recordSound(), RECORD_SIZE);
	// babel.getMedia().setAudioStreamState(false);
	return babel.run();
}
