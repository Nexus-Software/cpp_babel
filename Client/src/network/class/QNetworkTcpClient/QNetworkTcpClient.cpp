#include <iostream>
#include "QNetworkTcpClient.hpp"
#include "NetworkManager.hpp"

babel::QNetworkTcpClient::QNetworkTcpClient(babel::NetworkManager& manager)
:
	_manager(manager),
	_socket(std::make_shared<QTcpSocket>())
{
	this->_in.setDevice(this->_socket.get());
    this->_in.setVersion(QDataStream::Qt_4_0);

    QObject::connect(this->_socket.get(), SIGNAL(connected()), this, SLOT(connected()));
    QObject::connect(this->_socket.get(), SIGNAL(readyRead()), this, SLOT(readEvent()));
    QObject::connect(this->_socket.get(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &QNetworkTcpClient::displayError);
}

babel::QNetworkTcpClient::~QNetworkTcpClient()
{
	std::cout << "QNetworkTcpClient destructed" << std::endl;
}

bool babel::QNetworkTcpClient::connectToTcpHost(const std::string& ip, int port)
{
	std::cout << "Connection to the host at " << ip << ":" << port << std::endl;
	this->_socket->abort();
	this->_socket->connectToHost(QString::fromStdString(ip), port);
	return true;
}

bool babel::QNetworkTcpClient::disconnect()
{
	std::cout << "About to disconnect from the host" << std::endl;
    this->_socket->disconnectFromHost();
	return true;
}

bool babel::QNetworkTcpClient::write(babel::t_babelPackedData& st)
{
	if(this->_socket->state() == QAbstractSocket::ConnectedState)
	{
		QByteArray ba(reinterpret_cast<char *>(&st), sizeof(st));
		this->_socket->write(ba);
		return true;
	}
	else
		return false;
}

bool babel::QNetworkTcpClient::connected()
{
    std::cout << "Connected !" << std::endl;
	return true;
}

bool babel::QNetworkTcpClient::readEvent()
{
	std::cout << "New transmission incoming" << std::endl;
	std::cout << "Bytes available: (begin)" << this->_socket->bytesAvailable() << std::endl;
	while (this->_socket->bytesAvailable() >= sizeof(babel::t_babelPackedData)) {
		std::cout << "loop> Bytes available: " << this->_socket->bytesAvailable() << std::endl;
		this->_manager.handleCmd(*(reinterpret_cast<babel::t_babelPackedData*>(this->_socket->read(sizeof(babel::t_babelPackedData)).data())));
	}
	return true;
}

bool babel::QNetworkTcpClient::displayError(QAbstractSocket::SocketError socketError)
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