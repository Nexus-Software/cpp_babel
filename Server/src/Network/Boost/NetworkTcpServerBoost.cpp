/*
** NetworkTcpServerBoost.cpp for Server in /home/enguerrand/delivery/Server/NetworkTcpServerBoost.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
** Last update jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
*/

#include "Server.hpp"
#include "NetworkTcpServerBoost.hpp"
#include "NetworkManagerBoost.hpp"

babel::NetworkTcpServerBoost::NetworkTcpServerBoost(Server &server, NetworkManagerBoost &networkManager,  unsigned int port):
	_server(server),
	_networkManager(networkManager),
	_port(port),
	_acceptor(this->_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), static_cast<unsigned short>(port)))
{
  try
    {
      this->_server.getLogInTerm().print("TCP Server (Boost): Initisalisation on port " + std::to_string(port) + " ... ...", LogInTerm::LevelLog::INFO);
    }
  catch (...)
    {
      std::cerr << "TCP SERVER ERROR: " << std::endl;
    }
}

babel::NetworkTcpServerBoost::~NetworkTcpServerBoost()
{
  this->_server.getLogInTerm().print("TCP Server (Boost): Stop in few seconds", LogInTerm::LevelLog::INFO);
  this->_ioService.stop();
  this->_threadIoService.get()->join();
  this->_server.getLogInTerm().print("TCP Server (Boost): Stop", LogInTerm::LevelLog::INFO);
}

void babel::NetworkTcpServerBoost::waitClient()
{
  this->_server.getLogInTerm().print("TCP Server (Boost): Wait client", LogInTerm::LevelLog::INFO);
  boost::shared_ptr<NetworkTcpServerTunnelBoost> newConnection =
	  NetworkTcpServerTunnelBoost::create(this->_server, this->_acceptor.get_io_service());

  this->_acceptor.async_accept(newConnection->socket(), boost::bind(&NetworkTcpServerBoost::handle_accept, this, newConnection, boost::asio::placeholders::error));

  this->_threadIoService = boost::shared_ptr<boost::thread>(new boost::thread(&NetworkTcpServerBoost::runIoServer, this));
}

void babel::NetworkTcpServerBoost::handle_accept(NetworkTcpServerTunnelBoost::pointer newConnection, const boost::system::error_code& error)
{
  if (!error)
    {
      this->_networkManager.addTunnel(newConnection);
      newConnection->start();
    }
  else
    {
      this->_server.getLogInTerm().print("TCP Server (Boost): " + error.message(), LogInTerm::LevelLog::ERROR);
    }
  this->waitClient();
}

void babel::NetworkTcpServerBoost::runIoServer()
{
  while(1) {
      try {
	  this->_server.getLogInTerm().print("TCP Server (Boost): Run io_service", LogInTerm::LevelLog::INFO);
	  this->_ioService.run();
	} catch( const boost::system::system_error& e ) {
	  std::cerr << e.what() << std::endl;
	}
    }
}
