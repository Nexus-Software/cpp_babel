#include "QNetworkUdp.hpp"
#include "NetworkManager.hpp"

babel::QNetworkUdp::QNetworkUdp(NetworkManager& ancestor)
	:
	_manager(ancestor),
	_socket(std::make_shared<QUdpSocket>()),
	_server(std::make_shared<QUdpSocket>())
{
	QObject::connect(this->_server.get(), SIGNAL(readyRead()), this, SLOT(readEvent()));
	QObject::connect(this->_socket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &QNetworkUdp::displayError);
}

babel::QNetworkUdp::~QNetworkUdp()
{
}

bool babel::QNetworkUdp::clientWrite(babel::t_clientUdpPacket& t)
{
	std::cout << t._header.login << std::endl;
	return false;
}

bool babel::QNetworkUdp::serverBind(std::uint32_t port)
{
	this->_server->bind(QHostAddress::LocalHost, port);
	return true;
}

bool babel::QNetworkUdp::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(this, tr("Fortune Client"), tr("The host was not found. Please check the host name and port settings."));
		break;
	case QAbstractSocket::ConnectionRefusedError:
		QMessageBox::information(this, tr("Fortune Client"), tr("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct."));
		break;
	default:
		QMessageBox::information(this, tr("Fortune Client"), tr("The following error occurred: %1.").arg(this->_socket->errorString()));
	}
	return true;
}