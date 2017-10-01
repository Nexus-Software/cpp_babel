#include "QNetworkUdp.hpp"
#include "NetworkManager.hpp"

babel::QNetworkUdp::QNetworkUdp(NetworkManager& ancestor)
	:
	_manager(ancestor),
	_server(std::make_shared<QUdpSocket>())
{
	QObject::connect(this->_server.get(), SIGNAL(readyRead()), this, SLOT(readEvent()));
	QObject::connect(this->_server.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &QNetworkUdp::displayError);
}

babel::QNetworkUdp::~QNetworkUdp()
{
}

bool babel::QNetworkUdp::readEvent()
{
	std::cout << "New UDP transmission incoming" << std::endl;
	std::cout << "--- Bytes available: (begin)" << this->_server->bytesAvailable() << std::endl;
	while (this->_server->hasPendingDatagrams()) {
		QByteArray buffer;
		buffer.resize(this->_server->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		this->_server->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
		std::cout << "New data from " << sender.toString().toStdString() << " at port(" << senderPort << "): " << buffer.data() << std::endl;

	}
	std::cout << "End of UDP transmission" << std::endl;
	return true;
}

bool babel::QNetworkUdp::clientWrite(const std::string& data, const std::string& ipHost, std::uint32_t port)
{
	QByteArray buffer;
	buffer.resize(data.size());
	QHostAddress host(QString::fromStdString(ipHost));
	quint16 senderPort = port;

	buffer = data.data();
	std::cout << "Creation of UDP packet for " << host.toIPv4Address() << " at " << senderPort << ": " << buffer.data() << std::endl;
	this->_server->writeDatagram(buffer.data(), buffer.size(), host, senderPort);
	return false;
}

bool babel::QNetworkUdp::serverBind(std::uint32_t port)
{
	this->_server->close();
	this->_server->bind(QHostAddress::AnyIPv4, port);
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
			QMessageBox::information(this, tr("Fortune Client"), tr("The following error occurred: %1.").arg(this->_server->errorString()));
	}
	return true;
}