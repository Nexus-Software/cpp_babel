#include <iostream>
#include "QNetworkTcpClient.hpp"

babel::QNetworkTcpClient::QNetworkTcpClient()
:
	_socket(new QTcpSocket()),
	_session(Q_NULLPTR)
{
	this->_in.setDevice(this->_socket);
    this->_in.setVersion(QDataStream::Qt_4_0);

    QObject::connect(this->_socket, SIGNAL(connected()), this, SLOT(connected()));
    QObject::connect(this->_socket, SIGNAL(readyRead()), this, SLOT(readEvent()));
    QObject::connect(this->_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &QNetworkTcpClient::displayError);
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

bool babel::QNetworkTcpClient::write(const babel::t_babelPackedData& st)
{
	if(this->_socket->state() == QAbstractSocket::ConnectedState)
	{
		babel::t_babelPackedData dataToWrite = st;
		QByteArray ba(reinterpret_cast<char *>(&dataToWrite), sizeof(dataToWrite));
		this->_socket->write(ba);
		return true;
	}
	else
		return false;
}

bool babel::QNetworkTcpClient::connected()
{
    std::cout << "Connected !" << std::endl;
    // TODO: REMOVE that, it's an example
    std::array<char, 2048> ba = {0};
   	std::string username = "Admin\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	std::string password = "Pass\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	std::copy(username.begin(), username.end(), ba.begin());
	std::copy(password.begin(), password.end(), ba.begin() + 32);
	babel::t_babelPackedData t;
	t.code = 1;
	t.size = 64;
	t.data = ba;
	// ---------------------------
    this->write(t);
}

bool babel::QNetworkTcpClient::readEvent()
{
    std::cout << "read event triggered" << std::endl;
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