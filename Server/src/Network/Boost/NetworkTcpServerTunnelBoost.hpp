/*
** NetworkTcpServerTunnelBoost.hpp for Server in /home/enguerrand/delivery/Server/NetworkTcpServerTunnelBoost.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 15:18:31 2017 Enguerrand Allamel
** Last update jeu. sept. 21 15:18:31 2017 Enguerrand Allamel
*/

#ifndef SERVER_NETWORKTCPSERVERTUNNELBOOST_HPP
#define SERVER_NETWORKTCPSERVERTUNNELBOOST_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include "BabelNetworkMacro.hpp"

namespace babel {
  class Server;

  class NetworkTcpServerTunnelBoost : public boost::enable_shared_from_this<NetworkTcpServerTunnelBoost>
  {
   protected:
    struct Header
    {
      std::uint32_t	_actionCode;
      std::uint32_t	_dataSize;
    };

   protected:
    Server					&_server;
    boost::asio::ip::tcp::socket	 	_socket;

    Header					_headerRead;
    boost::array<char, B_NETWORK_BUFFER_SIZE>	_dataRead;
   public:
    typedef boost::shared_ptr<NetworkTcpServerTunnelBoost> pointer;

    static pointer create(Server &server, boost::asio::io_service& io_service)
    {
      return pointer(new NetworkTcpServerTunnelBoost(server, io_service));
    }

    boost::asio::ip::tcp::socket& socket()
    {
      return this->_socket;
    }

    void start();
   public:
    NetworkTcpServerTunnelBoost(Server &server, boost::asio::io_service& io_service);

    template <typename T> void write(const unsigned int size, T data);

    virtual const bool close() const;

   private:
    void readHeader();
    void readData();

    void handleHeaderRead(const boost::system::error_code& error);
    void handleDataRead(const boost::system::error_code& error);

    void handleWrite(const boost::system::error_code &error);
  };
}

#endif //SERVER_NETWORKTCPSERVERTUNNELBOOST_HPP
