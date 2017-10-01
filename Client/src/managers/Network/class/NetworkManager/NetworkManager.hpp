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
			const std::shared_ptr<INetworkUdp> getNetworkUdp(void) const;
			std::shared_ptr<INetworkUdp> getNetworkUdp(void);
			void sendRecordToCall(const std::vector<unsigned char>&);
			void handleCmd(babel::t_babelPackedData&);
			void writeServerTCP(babel::t_babelPackedData&);
			void writeServerTCP(std::uint32_t, std::uint32_t, std::array<char, 2048>);
			void C_Success(babel::t_babelPackedData & t);
			void C_SuccessJoin(babel::t_babelPackedData & t);
			void C_SuccessLogin(babel::t_babelPackedData & t);
			void C_SuccessSignUp(babel::t_babelPackedData & t);
			void C_SuccessDel(babel::t_babelPackedData & t);
			void C_SuccessAdd(babel::t_babelPackedData & t);
			void C_SuccessInvite(babel::t_babelPackedData & t);
			void C_SuccessLeave(babel::t_babelPackedData & t);
			void C_InternalError(babel::t_babelPackedData & t);
			void C_ErrorAlreadyUsed(babel::t_babelPackedData & t);
			void C_ErrorWrongCreds(babel::t_babelPackedData & t);
			void C_ErrorUserNotFound(babel::t_babelPackedData & t);
			void C_ConvNotFound(babel::t_babelPackedData & t);
			void C_GetContactList(babel::t_babelPackedData & t);
			void C_GetCallInvitation(babel::t_babelPackedData & t);
			void C_NotifyLeaveCall(babel::t_babelPackedData & t);
			void C_NotifyUserJoinConv(babel::t_babelPackedData & t);
	};
}

#endif // !BABEL_NETWORKMANAGER_HPP_
