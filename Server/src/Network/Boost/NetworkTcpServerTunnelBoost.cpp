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
	_socket(io_service),
	_tunnelId(0)
{
}

void babel::NetworkTcpServerTunnelBoost::start()
{
  this->_ip = this->_socket.remote_endpoint().address().to_string();
  this->_server.getNetworkManager().get()->setIpForTunnelId(this->_tunnelId, this->_ip);
  this->read();
}

void babel::NetworkTcpServerTunnelBoost::write(NetworkData data)
{
  boost::asio::async_write(this->_socket,
			   boost::asio::buffer(&data, sizeof(NetworkData)),
			   boost::bind(&NetworkTcpServerTunnelBoost::handleWrite, shared_from_this(), boost::asio::placeholders::error));

}

void babel::NetworkTcpServerTunnelBoost::close()
{
  this->_socket.close();
  this->_server.getNetworkManager().get()->closeTunnel(this->_tunnelId);
}

void babel::NetworkTcpServerTunnelBoost::handleWrite(const boost::system::error_code &error)
{
  if (error)
    {
      this->close();
    }
}

void babel::NetworkTcpServerTunnelBoost::read()
{
  boost::asio::async_read(this->_socket,
			  boost::asio::buffer(&this->_dataRead, sizeof(NetworkData)),
			  boost::asio::transfer_at_least(sizeof(NetworkData)),
			  boost::bind(&NetworkTcpServerTunnelBoost::handleRead, shared_from_this(), boost::asio::placeholders::error)
  );
}

void babel::NetworkTcpServerTunnelBoost::handleRead(const boost::system::error_code &error)
{
  if (!error)
    {

      this->_server.getHandleCmd().execCmd(this->_tunnelId, this->_dataRead);
      this->_dataRead.data = {0};
      this->read();
    }
  else
    {
      this->close();
    }
}

const size_t &babel::NetworkTcpServerTunnelBoost::getTunnelId() const
{
  return this->_tunnelId;
}

void babel::NetworkTcpServerTunnelBoost::setTunnelId(size_t tunnelId)
{
  this->_tunnelId = tunnelId;
}

const std::string &babel::NetworkTcpServerTunnelBoost::getIp() const
{
  return this->_ip;
}
