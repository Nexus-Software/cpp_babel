#include "BabelClientManager.hpp"

int main(int argc, char **argv)
{
    babel::BabelClientManager babel(argc, argv);

    return babel.run();
}
