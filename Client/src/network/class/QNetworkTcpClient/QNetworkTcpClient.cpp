#include <iostream>
#include "QNetworkTcpClient.hpp"

babel::QNetworkTcpClient::QNetworkTcpClient()
:
	_socket(new QTcpSocket()),
	_session(Q_NULLPTR)
{
	this->_in.setDevice(this->_socket);
    this->_in.setVersion(QDataStream::Qt_4_0);

    QObject::connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readEvent()));
    QObject::connect(this->_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &QNetworkTcpClient::displayError);
    // connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
	std::cout << "QNetworkTcpClient created" << std::endl;
}

babel::QNetworkTcpClient::~QNetworkTcpClient()
{
	std::cout << "QNetworkTcpClient destructed" << std::endl;
}

bool babel::QNetworkTcpClient::connectToTcpHost(const std::string& ip, int port)
{
	std::cout << "Connection to the host" << std::endl;
	this->_socket->abort();
	this->_socket->connectToHost(QString::fromStdString(ip), port);
	return true;
}

bool babel::QNetworkTcpClient::disconnect()
{
	std::cout << "About to disconnect from the host" << std::endl;
	// Disconnect from host and close all connections
	return true;
}

bool babel::QNetworkTcpClient::write()
{
	// write some data for the host
	return true;
}

bool babel::QNetworkTcpClient::readEvent()
{
	this->_in.startTransaction();

	std::cout << "New data available, reading it..." << std::endl;
    QString nextFortune;
    this->_in >> nextFortune;

    if (!this->_in.commitTransaction())
        return false;

    std::cout << "Get: " << nextFortune.toStdString() << std::endl;
	return true;
}

bool babel::QNetworkTcpClient::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(this->_socket->errorString()));
    }
	return true;
}