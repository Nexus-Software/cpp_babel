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


void babel::NetworkTcpServerTunnelBoost::write(dataToWrite data)
{
  boost::asio::async_write(this->_socket,
			   boost::asio::buffer(data.data, data.size),
			   boost::bind(&NetworkTcpServerTunnelBoost::handleWrite, shared_from_this(), boost::asio::placeholders::error));

}

void babel::NetworkTcpServerTunnelBoost::close()
{
  this->_socket.close();
}

void babel::NetworkTcpServerTunnelBoost::handleWrite(const boost::system::error_code &error)
{
  // Todo: Not implement yet (check error)
  if (error)
    {
    }
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
  else
    {

    }
}

void babel::NetworkTcpServerTunnelBoost::handleDataRead(const boost::system::error_code &error)
{
  if (!error)
    {
      std::cout << "Data: " << std::string(reinterpret_cast<const char *>(this->_dataRead.data()), this->_dataRead.size())
		<< std::endl;
      // Exec cmd
      // Fake write for test
      dataToWrite data;
      std::uint32_t nb = 32;
      data.size = sizeof(std::uint32_t);
      data.data = &nb;
      this->write(data);
      nb = 342;
      data.size = sizeof(std::uint32_t);
      data.data = &nb;
      this->write(data);

      //
      this->_headerRead._dataSize = 0;
      this->_headerRead._actionCode = 0;
      this->readHeader();
    }
  else
    {

    }
}