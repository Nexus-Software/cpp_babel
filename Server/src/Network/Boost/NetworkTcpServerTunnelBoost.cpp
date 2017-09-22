/*
** NetworkTcpServerTunnelBoost.cpp for Server in /home/enguerrand/delivery/Server/NetworkTcpServerTunnelBoost.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 15:18:31 2017 Enguerrand Allamel
** Last update jeu. sept. 21 15:18:31 2017 Enguerrand Allamel
*/

#include "NetworkTcpServerTunnelBoost.hpp"
#include "Server.hpp"

babel::NetworkTcpServerTunnelBoost::NetworkTcpServerTunnelBoost(Server &server, boost::asio::io_service& io_service):
	_server(server),
	_socket(io_service)
{
}

void babel::NetworkTcpServerTunnelBoost::start()
{
  this->_server.getLogInTerm().print("TCP Server (Boost): New tunnel", LogInTerm::LevelLog::INFO);
}

void babel::NetworkTcpServerTunnelBoost::read(const unsigned int size)
{

}

void babel::NetworkTcpServerTunnelBoost::write(const unsigned int size,
					       const char buffer[B_NETWORK_BUFFER_SIZE])
{

}

const bool babel::NetworkTcpServerTunnelBoost::close() const
{
  return 0;
}
