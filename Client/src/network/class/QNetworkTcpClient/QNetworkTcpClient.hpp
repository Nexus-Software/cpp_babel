#ifndef Q_NETWORK_TCP_CLIENT_HPP
#define Q_NETWORK_TCP_CLIENT_HPP

#include <QtNetwork>
#include <QtWidgets>
#include <QTcpSocket>
#include <QDataStream>
#include "INetworkTcpClient.hpp"

namespace babel {
	class QNetworkTcpClient : public QWidget, public INetworkTcpClient
	{
		Q_OBJECT

		public:
			QNetworkTcpClient();
			virtual ~QNetworkTcpClient();

		private:
			QTcpSocket*			_socket;
			QDataStream			_in;
            QNetworkSession*	_session;
		
		public:
			virtual bool connectToTcpHost(const std::string&, int);
			virtual bool write(void);
			virtual bool disconnect(void);

		public slots:
			bool readEvent(void);
			bool displayError(QAbstractSocket::SocketError socketError);
	};
} // babel

#endif // Q_NETWORK_TCP_CLIENT_HPP
