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
		public:
			QNetworkUdp(NetworkManager&);
			~QNetworkUdp();

		private:
			NetworkManager&					_manager;
			std::shared_ptr<QUdpSocket>		_socket;

		public:
			virtual bool write(babel::t_clientUdpPacket&);

	};
}

#endif // !BABEL_QNETWORKUDP_HPP
