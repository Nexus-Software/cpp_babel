#ifndef Q_NETWORK_TCP_CLIENT_HPP
#define Q_NETWORK_TCP_CLIENT_HPP

#include <stdint.h>
#include <QtNetwork>
#include <QtWidgets>
#include <QTcpSocket>
#include <QDataStream>
#include <algorithm>
#include <memory>
#include "INetworkTcpClient.hpp"

namespace babel {
	class NetworkManager;
}

namespace babel {
	class QNetworkTcpClient : public QWidget, public INetworkTcpClient
	{
		Q_OBJECT

		public:
			QNetworkTcpClient(NetworkManager&);
			virtual ~QNetworkTcpClient();

		private:
			NetworkManager&					_manager;
			std::shared_ptr<QTcpSocket>		_socket;
			QDataStream						_in;
		
		public:
			virtual bool connectToTcpHost(const std::string&, int);
			virtual bool write(babel::t_babelPackedData&);
			virtual bool disconnect(void);

		public slots:
			bool connected(void);
			bool readEvent(void);
			bool displayError(QAbstractSocket::SocketError socketError);
	};
} // babel

#endif // Q_NETWORK_TCP_CLIENT_HPP
