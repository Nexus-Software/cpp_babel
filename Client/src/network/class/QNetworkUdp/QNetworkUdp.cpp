#include "QNetworkUdp.hpp"
#include "NetworkManager.hpp"
#include "BabelClientManager.hpp"

babel::QNetworkUdp::QNetworkUdp(NetworkManager& ancestor)
	:
	_manager(ancestor),
	_server(std::make_shared<QUdpSocket>())
{
	QObject::connect(this->_server.get(), SIGNAL(readyRead()), this, SLOT(readEvent()));
}

babel::QNetworkUdp::~QNetworkUdp()
{
}

bool babel::QNetworkUdp::readEvent()
{
	std::cout << "New UDP transmission incoming" << std::endl;
	std::cout << "--- Bytes available: (begin)" << this->_server->bytesAvailable() << std::endl;

	std::mutex lock;

	while (this->_server->hasPendingDatagrams()) {
		
		QByteArray buffer;
		buffer.resize(this->_server->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		
		this->_server->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
		unsigned char* buf2 = reinterpret_cast<unsigned char*>(buffer.data());
		std::vector<unsigned char>::size_type size = strlen((const char*)buffer);
		std::vector<unsigned char>in(buf2, buf2 + size);
		lock.lock();
		EncodedData eData(in.size(), in);
		babel::Codec codec;
		B_SAMPLE out;
		codec.Decode(eData, out);
		this->_manager.getRoot().getMedia().playSound(out);
		lock.unlock();
	}
	std::cout << "End of UDP transmission" << std::endl;
	return true;
}

bool babel::QNetworkUdp::clientWrite(const std::vector<unsigned char>& data, const std::string& ipHost, std::uint32_t port)
{
	QByteArray buffer;
	buffer.resize(data.size());
	buffer = reinterpret_cast<const char*>(data.data());

	QHostAddress host(QString::fromStdString(ipHost));

	this->_server->writeDatagram(buffer.data(), buffer.size(), host, port);
	return false;
}

bool babel::QNetworkUdp::serverBind(std::uint32_t port)
{
	this->_server->bind(QHostAddress::Any, port, QUdpSocket::ReuseAddressHint | QAbstractSocket::ShareAddress);
	return true;
}