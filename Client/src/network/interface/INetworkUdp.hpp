#ifndef I_NETWORK_UDP_CLIENT_HPP
#define I_NETWORK_UDP_CLIENT_HPP

#include <vector>
#include "stdint.h"

#pragma pack(push, 1)

namespace babel {
	typedef struct		s_clientUdpHeader
	{
		char			login[32];
		std::uint32_t	type;
		std::uint32_t	size;
	}					t_clientUdpHeader;

	typedef struct			s_clientUdpPacket
	{
		t_clientUdpHeader	_header;
		std::vector<char>	_data;
	}						t_clientUdpPacket;
} // babel

#pragma pack(pop)

namespace babel {
	class INetworkUdp
	{
	public:
		virtual ~INetworkUdp(void) {}

	public:
		virtual bool clientWrite(babel::t_clientUdpPacket&) = 0;
		virtual bool serverBind(std::uint32_t) = 0;

	};
} // babel

#endif // I_NETWORK_TCP_CLIENT_HPP
