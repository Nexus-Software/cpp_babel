#ifndef I_NETWORK_TCP_CLIENT_HPP
#define I_NETWORK_TCP_CLIENT_HPP

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
	class INetworkTcpClient
	{
		public:
            virtual ~INetworkTcpClient(void) {}
	
		public:
			virtual bool connectToTcpHost(const std::string&, int)	= 0;
			virtual bool write(const babel::t_babelPackedData&)		= 0;
			virtual bool disconnect(void)							= 0;
	};
} // babel

#endif // I_NETWORK_TCP_CLIENT_HPP
