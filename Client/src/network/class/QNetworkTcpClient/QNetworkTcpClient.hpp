#ifndef Q_NETWORK_TCP_CLIENT_HPP
#define Q_NETWORK_TCP_CLIENT_HPP

#include <stdint.h>
#include <QtNetwork>
#include <QtWidgets>
#include <QTcpSocket>
#include <QDataStream>
#include <algorithm>
#include "INetworkTcpClient.hpp"

#pragma pack(push, 1)

namespace babel {
	typedef struct 	s_babelPackedData
	{
		std::uint32_t			code;
		std::uint32_t			size;
		std::array<char, 2048>	data;
	}				t_babelPackedData;
} // babel

#pragma pack(pop)

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
			bool connected(void);
			bool readEvent(void);
			bool displayError(QAbstractSocket::SocketError socketError);
	};
} // babel

#endif // Q_NETWORK_TCP_CLIENT_HPP
