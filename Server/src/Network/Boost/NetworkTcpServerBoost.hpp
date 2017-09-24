/*
** NetworkTcpServerBoost.hpp for Server in /home/enguerrand/delivery/Server/NetworkTcpServerBoost.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
** Last update jeu. sept. 21 13:32:55 2017 Enguerrand Allamel
*/

#ifndef SERVER_NETWORKTCPSERVERBOOST_HPP
#define SERVER_NETWORKTCPSERVERBOOST_HPP

#ifndef BOOST_ASIO_HAS_MOVE
 #define BOOST_ASIO_HAS_MOVE
#endif

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "NetworkTcpServerTunnelBoost.hpp"
#include "NetworkException.hpp"

namespace babel {
  class Server;
  class NetworkManagerBoost;

  class NetworkTcpServerBoost
  {
   protected:
    boost::asio::io_service 		_ioService;

    Server				&_server;
    NetworkManagerBoost			&_networkManager;

    unsigned int			_port;
    boost::shared_ptr<boost::thread>	_threadIoService;
    boost::asio::ip::tcp::acceptor 	_acceptor;
   public:
    NetworkTcpServerBoost(Server &server, NetworkManagerBoost &networkManager, unsigned int port);
    ~NetworkTcpServerBoost();

    void waitClient();

    void runIoServer();

   private:
    void handle_accept(NetworkTcpServerTunnelBoost::pointer new_connection, const boost::system::error_code& error);
  };
}

#endif //SERVER_NETWORKTCPSERVERBOOST_HPP
