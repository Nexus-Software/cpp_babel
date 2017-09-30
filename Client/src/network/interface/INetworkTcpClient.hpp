#ifndef I_NETWORK_TCP_CLIENT_HPP
#define I_NETWORK_TCP_CLIENT_HPP

#include <array>

namespace babel {
    typedef struct     s_babelPackedData
    {
        std::uint32_t            code;
        std::uint32_t            size;
        std::array<char, 2048>    data;
    }                t_babelPackedData;

    typedef struct        s_clientContactStruct
    {
        char            login[32];
        std::uint32_t    isOnline;
    }                    t_clientContactStruct;

    typedef struct        s_clientCallStruct
    {
        char            login[32];
        char            ip[16];
        std::uint32_t    port;
    }                    t_clientCallStruct;

    struct                    t_clientContactList
    {
        t_clientContactStruct contacts[50];
    };
} // babel

namespace babel {
	class INetworkTcpClient
	{
		public:
            virtual ~INetworkTcpClient(void) {}
	
		public:
			virtual bool connectToTcpHost(const std::string&, int)	= 0;
			virtual bool write(babel::t_babelPackedData&)		= 0;
			virtual bool disconnect(void)							= 0;
	};
} // babel

#endif // I_NETWORK_TCP_CLIENT_HPP
