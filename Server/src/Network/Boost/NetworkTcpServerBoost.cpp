/*
** NetworkTcpServerBoost.cpp for Server in /home/enguerrand/delivery/Server/NetworkTcpServerBoost.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
** Last update jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
*/

#include "NetworkTcpServerBoost.hpp"
#include "Server.hpp"

babel::NetworkTcpServerBoost::NetworkTcpServerBoost(Server &server, unsigned int port):
	_server(server),
	_port(port),
	_acceptor(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), static_cast<unsigned short>(_port)))
{
  try
    {
      this->_threadIoService = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &this->_ioService)));
      this->_server.getLogInTerm().print("TCP Server (Boost): Initisalisation ...", LogInTerm::LevelLog::INFO);
    }
  catch (std::exception& e)
    {
      std::cerr << "TCP SERVER ERROR: " << e.what() << std::endl;
    }
}

babel::NetworkTcpServerBoost::~NetworkTcpServerBoost()
{
  this->_ioService.stop();
  this->_threadIoService.get()->join();
  this->_server.getLogInTerm().print("TCP Server (Boost): Stop", LogInTerm::LevelLog::INFO);
}

void babel::NetworkTcpServerBoost::waitClient()
{
  NetworkTcpServerTunnelBoost::pointer newConnection =
	  NetworkTcpServerTunnelBoost::create(this->_server, this->_acceptor.get_io_service());

  this->_acceptor.async_accept(newConnection->socket(), boost::bind(&NetworkTcpServerBoost::handle_accept, this, newConnection, boost::asio::placeholders::error));
}

void babel::NetworkTcpServerBoost::handle_accept(NetworkTcpServerTunnelBoost::pointer newConnection, const boost::system::error_code& error)
{
  if (!error)
    {
      newConnection->start();
    }
  else
    {
      this->_server.getLogInTerm().print("TCP Server (Boost): " + error.message(), LogInTerm::LevelLog::ERROR);
    }
  this->waitClient();
}
