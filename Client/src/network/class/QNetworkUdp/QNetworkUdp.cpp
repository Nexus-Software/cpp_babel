#include "QNetworkUdp.hpp"
#include "NetworkManager.hpp"

babel::QNetworkUdp::QNetworkUdp(NetworkManager& ancestor)
	:
	_manager(ancestor),
	_socket(std::make_shared<QUdpSocket>())
{
}

babel::QNetworkUdp::~QNetworkUdp()
{
}

bool babel::QNetworkUdp::write(babel::t_clientUdpPacket& t)
{
	std::cout << t._header.login << std::endl;
	return false;
}
