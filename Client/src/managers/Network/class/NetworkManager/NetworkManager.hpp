#ifndef BABEL_NETWORKMANAGER_HPP_
# define BABEL_NETWORKMANAGER_HPP_

#include <memory>
#include "Status.hpp"
#include "QNetworkTcpClient.hpp"

# define IP_VPN "149.202.42.41"

namespace babel {
	class BabelClientManager;
} // babel

namespace babel {
	class NetworkManager
	{
		public:
			NetworkManager(babel::BabelClientManager&);
			~NetworkManager();

		private:
			babel::BabelClientManager&			_root;
			std::shared_ptr<INetworkTcpClient>	_networkTcp;

		public:
			babel::BabelClientManager& getRoot(void) const;
			const std::shared_ptr<INetworkTcpClient> getNetworkTcp(void) const;
			std::shared_ptr<INetworkTcpClient> getNetworkTcp(void);
	};
}

#endif // !BABEL_NETWORKMANAGER_HPP_
