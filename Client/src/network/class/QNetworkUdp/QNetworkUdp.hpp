#ifndef BABEL_QNETWORKUDP_HPP
# define BABEL_QNETWORKUDP_HPP

#include <memory>
#include <QtNetwork>
#include <mutex>
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
			virtual bool clientWrite(const std::vector<unsigned char>&, const std::string&, std::uint32_t);
			virtual bool serverBind(std::uint32_t);

		public slots:
			bool readEvent(void);
	};
}

#endif // !BABEL_QNETWORKUDP_HPP
