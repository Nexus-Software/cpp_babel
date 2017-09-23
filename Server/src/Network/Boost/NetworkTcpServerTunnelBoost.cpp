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
  this->readHeader();
}

void babel::NetworkTcpServerTunnelBoost::readData()
{
  boost::asio::async_read(this->_socket,
			  boost::asio::buffer(&this->_dataRead, this->_headerRead._dataSize),
			  boost::asio::transfer_at_least(this->_headerRead._dataSize),
			  boost::bind(&NetworkTcpServerTunnelBoost::handleDataRead, shared_from_this(), boost::asio::placeholders::error)
  );
}

void babel::NetworkTcpServerTunnelBoost::write(const unsigned int size,
					       const char buffer[B_NETWORK_BUFFER_SIZE])
{

}

const bool babel::NetworkTcpServerTunnelBoost::close() const
{
  return 0;
}

void babel::NetworkTcpServerTunnelBoost::readHeader()
{
  boost::asio::async_read(this->_socket,
			  boost::asio::buffer(&this->_headerRead, sizeof(NetworkTcpServerTunnelBoost::Header)),
			  boost::asio::transfer_at_least(sizeof(NetworkTcpServerTunnelBoost::Header)),
			  boost::bind(&NetworkTcpServerTunnelBoost::handleHeaderRead, shared_from_this(), boost::asio::placeholders::error)
  );
}

void babel::NetworkTcpServerTunnelBoost::handleHeaderRead(const boost::system::error_code &error)
{
  if (!error)
    {
      std::cout << "Header: " << this->_headerRead._actionCode << " - " << this->_headerRead._dataSize << std::endl;
      this->readData();
    }
}

void babel::NetworkTcpServerTunnelBoost::handleDataRead(const boost::system::error_code &error)
{
  if (!error)
    {
      std::cout << "Data: " << std::string(reinterpret_cast<const char *>(this->_dataRead.data()), this->_dataRead.size())
		<< std::endl;
      // Exec cmd
      this->_headerRead._dataSize = 0;
      this->_headerRead._actionCode = 0;
      this->readHeader();
    }
}