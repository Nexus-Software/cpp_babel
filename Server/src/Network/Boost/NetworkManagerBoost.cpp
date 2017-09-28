/*
** NetworkManagerBoost.cpp for Server in /home/enguerrand/delivery/Server/NetworkManagerBoost.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 11:25:19 2017 Enguerrand Allamel
** Last update dim. sept. 24 11:25:19 2017 Enguerrand Allamel
*/

#include "NetworkManagerBoost.hpp"
#include "Server.hpp"

babel::NetworkManagerBoost::NetworkManagerBoost(babel::Server &server, unsigned int port):
	_port(port),
	_server(server),
	_tcpServer(this->_server, *this, this->_port)
{
}

babel::NetworkManagerBoost::~NetworkManagerBoost()
{

}

void babel::NetworkManagerBoost::acceptClient()
{
  this->_tcpServer.waitClient();
}

bool babel::NetworkManagerBoost::write(size_t tunnelId, NetworkData data)
{
  try
    {
      auto tu = this->_tunnelList.at(tunnelId).get();
      tu->write(data);
      return true;
    }
  catch (std::out_of_range)

    {
      throw NetworkException("(Boost): Tunnel not found for write (ID:" + std::to_string(tunnelId) + ")");
    }
}

bool babel::NetworkManagerBoost::write(std::string login, NetworkData data)
{
  try
    {
      auto it = this->_tunnelInfo.begin();
      for (; it != this->_tunnelInfo.end() ; it++)
	{
	  if ((*it).second.login.compare((login)))
	    break ;
	}
      if (it == this->_tunnelInfo.end())
	throw NetworkException("(Boost): Tunnel not found for write (Login:" + login + ")");
      auto tu = this->_tunnelList.at((*it).first).get();
      tu->write(data);
      return true;
    }
  catch (std::out_of_range)

    {
      throw NetworkException("(Boost): Tunnel not found for write (ID:" + login + ")");
    }
}

bool babel::NetworkManagerBoost::writeForAll(NetworkData data)
{
  return (true);
}

void babel::NetworkManagerBoost::addTunnel(boost::shared_ptr<NetworkTcpServerTunnelBoost> tunnel)
{
  size_t newId = 0;

  while (this->_tunnelList.find(newId) != this->_tunnelList.end())
    newId += 1;
  this->_tunnelList.insert(std::pair<size_t, NetworkTcpServerTunnelBoost::pointer>(newId, tunnel));

  TunnelInfo tunnelInfo;

  tunnelInfo.id = newId;
  tunnelInfo.isAuth = false;
  tunnelInfo.login = std::string("");

  this->_tunnelInfo.insert(std::pair<size_t, TunnelInfo>(newId, tunnelInfo));

  tunnel.get()->setTunnelId(newId);

  this->_server.getLogInTerm().print("(Boost): Add in list new tunnel (" + std::to_string(newId) + ")", LogInTerm::LevelLog::INFO);
}

void babel::NetworkManagerBoost::removeTunnel(NetworkTcpServerTunnelBoost::pointer tunnel)
{
  size_t keyFound;

  for (auto it : this->_tunnelList)
    {
      if (it.second == tunnel)
	{
	  keyFound = it.first;
	  this->_tunnelList.erase(keyFound);
	  this->_tunnelInfo.erase(keyFound);
	  this->_server.getLogInTerm().print("(Boost) Delete in list tunnel (" + std::to_string(keyFound) + ")", LogInTerm::LevelLog::INFO);
	  break ;
	}
    }
}

babel::TunnelInfo babel::NetworkManagerBoost::getTunnelInfoByTunnelId(const size_t tunnelId)
{
  auto it = this->_tunnelInfo.find(tunnelId);
  if (it != this->_tunnelInfo.end())
    return (*it).second;
  throw NetworkException("(Boost): Tunnel not found (ID: " + std::to_string(tunnelId) + ")");
}

void babel::NetworkManagerBoost::setIpForTunnelId(size_t tunnelId, std::string ip)
{
  auto it = this->_tunnelInfo.find(tunnelId);
  if (it != this->_tunnelInfo.end())
    {
      (*it).second.ip = ip;
      return ;
    }
  throw NetworkException("(Boost): Tunnel not found (ID: " + std::to_string(tunnelId) + ")");
}

