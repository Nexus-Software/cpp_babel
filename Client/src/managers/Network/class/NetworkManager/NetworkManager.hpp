#ifndef BABEL_NETWORKMANAGER_HPP_
# define BABEL_NETWORKMANAGER_HPP_

#include <memory>
#include <functional>
#include <unordered_map>
#include "Status.hpp"
#include "QNetworkTcpClient.hpp"
#include "QNetworkUdp.hpp"

# define IP_MAIN_SERVER "10.101.54.29"
# define SERVER_PORT 42420

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
			babel::BabelClientManager&									_root;
			std::shared_ptr<INetworkTcpClient>							_networkTcp;
			std::shared_ptr<INetworkUdp>								_networkUdp;
			std::unordered_map<std::uint32_t, std::function<void(babel::t_babelPackedData)>>	_cmds;

		public:
			babel::BabelClientManager& getRoot(void) const;
			const std::shared_ptr<INetworkTcpClient> getNetworkTcp(void) const;
			std::shared_ptr<INetworkTcpClient> getNetworkTcp(void);
			void handleCmd(babel::t_babelPackedData&);
			void writeServerTCP(babel::t_babelPackedData&);
			void writeServerTCP(std::uint32_t, std::uint32_t, std::array<char, 2048>);
	};
}

#endif // !BABEL_NETWORKMANAGER_HPP_
