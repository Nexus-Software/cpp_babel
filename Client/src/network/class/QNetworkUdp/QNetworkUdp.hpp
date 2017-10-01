#ifndef BABEL_QNETWORKUDP_HPP
# define BABEL_QNETWORKUDP_HPP

#include <memory>
#include <QtNetwork>
#include <QtWidgets>
#include <QDataStream>
#include <QUdpSocket>
#include "INetworkUdp.hpp"

namespace babel {
	class NetworkManager;
}

namespace babel {
	class QNetworkUdp : public QWidget, public INetworkUdp
	{
		Q_OBJECT

		public:
			QNetworkUdp(NetworkManager&);
			~QNetworkUdp();

		private:
			NetworkManager&					_manager;
			std::shared_ptr<QUdpSocket>		_server;

		public:
			virtual bool clientWrite(const std::string&, const std::string&, std::uint32_t);
			virtual bool serverBind(std::uint32_t);

		public slots:
			bool readEvent(void);
			bool displayError(QAbstractSocket::SocketError socketError);

	};
}

#endif // !BABEL_QNETWORKUDP_HPP
