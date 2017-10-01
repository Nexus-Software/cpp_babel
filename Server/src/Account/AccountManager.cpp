/*
** AccountManager.cpp for Server in /home/enguerrand/delivery/Server/AccountManager.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 23:44:12 2017 Enguerrand Allamel
** Last update dim. sept. 24 23:44:12 2017 Enguerrand Allamel
*/

#include "AccountManager.hpp"
#include "Server.hpp"

babel::AccountManager::AccountManager(babel::Server &server):
	_server(server)
{

}

babel::AccountManager::~AccountManager()
{
}

bool babel::AccountManager::add(std::string login, std::string password)
{
  if (this->_accountList.find(login) != this->_accountList.end())
    return false;
  this->_accountList.insert(std::pair<std::string, Account>(login, Account(login, password)));
  return true;
}

bool babel::AccountManager::remove(std::string login)
{
  if (this->_accountList.find(login) != this->_accountList.end())
    {
      this->_accountList.erase(login);
      return true;
    }
  return false;
}

babel::Account & babel::AccountManager::getAccountByLogin(const std::string login)
{
  auto it = this->_accountList.find(login);
  if (it != this->_accountList.end())
    return (*it).second;
  throw babel::AccountManagerException("Account not found for login: " + login);
}

babel::Account const & babel::AccountManager::getAccountByLogin(const std::string login) const
{
  auto it = this->_accountList.find(login);
  if (it != this->_accountList.end())
    return (*it).second;
  throw babel::AccountManagerException("Account not found for login: " + login);
}

const std::unordered_map<std::string, babel::Account> &babel::AccountManager::getAccountList() const
{
  return this->_accountList;
}


bool babel::AccountManager::addContact(const std::string &login_req, const std::string &login)
{
  try
    {
      if (!this->getAccountByLogin(login).addContact(login_req) || !this->getAccountByLogin(login_req).addContact(login))
	return false;
      return true;
    }
  catch (babel::AccountManagerException)
    {
      return false;
    }
}

bool babel::AccountManager::removeContact(const std::string &login_req, const std::string &login)
{
  try
    {
      if (!this->getAccountByLogin(login).removeContact(login_req) || !this->getAccountByLogin(login_req).removeContact(login))
	return false;
    }
  catch (babel::AccountManagerException)
    {
      return false;
    }
  return true;
}

void babel::AccountManager::sendContactList(size_t tunnelId, std::string login)
{
  NetworkDataSCContactList networkDataSCContactList = {0};

  int i = 0;
  try
    {
      Account & account = this->getAccountByLogin(login);
      if (!this->_accountList.find(login)->second.getContactList().empty())
	{
	  for (auto it : this->_accountList.find(login)->second.getContactList())
	    {
	      this->_accountList.find(it)->second.getLogin().copy(networkDataSCContactList.contacts[i].login, 32);
	      networkDataSCContactList.contacts[i].isOnline = this->_accountList.find(it)->second.getIsOnline() ? 1 : 0;
	      std::cout << "Login: " << networkDataSCContactList.contacts[i].login << "Online:" << networkDataSCContactList.contacts[i].isOnline  << std::endl;
	      i += 1;
	    }
	}
      std::array<char, 2048> dataSend = {0};
      std::copy_n(reinterpret_cast<char *>(&networkDataSCContactList), sizeof(NetworkDataSCContactList), dataSend.data());

      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(6, sizeof(networkDataSCContactList), dataSend));
    }
  catch (AccountManagerException)
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(501, 0, {}));
      return ;
    }
}

bool babel::AccountManager::login(std::string login)
{
  try
    {
      Account & account = this->getAccountByLogin(login);

      if (account.getIsOnline())
	return false;
      account.setIsOnline(true);
      auto contactList = this->getAccountByLogin(login).getContactList();
      for (auto it : contactList)
	{
	  if (this->getAccountByLogin(it).getIsOnline())
	    this->sendContactList(this->_server.getNetworkManager().get()->getTunnelIdByLogin(it), it);
	}
      return true;
    }
  catch (AccountManagerException)
    {
      return false;
    }
  catch (NetworkManagerException)
    {
      return false;
    }
}

bool babel::AccountManager::leave(std::string login)
{
  try
    {
      Account & account = this->getAccountByLogin(login);

      if (!account.getIsOnline())
	return false;
      account.setIsOnline(false);
      auto contactList = this->getAccountByLogin(login).getContactList();
      for (auto it : contactList)
	{
 	  if (this->getAccountByLogin(it).getIsOnline())
	    this->sendContactList(this->_server.getNetworkManager().get()->getTunnelIdByLogin(it), it);
	}
      return true;
    }
  catch (AccountManagerException)
    {
      return false;
    }
  catch (NetworkManagerException)
    {
      return false;
    }
}