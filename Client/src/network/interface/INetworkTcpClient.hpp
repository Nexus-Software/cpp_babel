#ifndef I_NETWORK_TCP_CLIENT_HPP
#define I_NETWORK_TCP_CLIENT_HPP

namespace babel {
	class INetworkTcpClient
	{
		public:
            virtual ~INetworkTcpClient(void) {}
	
		public:
			virtual bool connectToTcpHost(const std::string&, int)	= 0;
			virtual bool write(void)								= 0;
			virtual bool disconnect(void)							= 0;
	};
} // babel

#endif // I_NETWORK_TCP_CLIENT_HPP
