#ifndef I_NETWORK_UDP_CLIENT_HPP
#define I_NETWORK_UDP_CLIENT_HPP

#include <string>
#include "stdint.h"

namespace babel {
	class INetworkUdp
	{
	public:
		virtual ~INetworkUdp(void) {}

	public:
		virtual bool clientWrite(const std::string&, const std::string&, std::uint32_t) = 0;
		virtual bool serverBind(std::uint32_t) = 0;

	};
} // babel

#endif // I_NETWORK_TCP_CLIENT_HPP
