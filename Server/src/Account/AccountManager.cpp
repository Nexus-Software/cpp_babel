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

babel::Account babel::AccountManager::getAccountByLogin(const std::string login)
{
  std::unordered_map<std::string, Account>::iterator it;

  if ((it = this->_accountList.find(login)) != this->_accountList.end())
    return (*it).second;
  throw babel::AccountManagerException("Account not found for login: " + login);
}

babel::Account const babel::AccountManager::getAccountByLogin(const std::string login) const
{
  std::unordered_map<std::string, Account>::const_iterator it;

  if ((it = this->_accountList.find(login)) != this->_accountList.end())
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
      this->_server.getAccountManager().getAccountByLogin(login);
    }
  catch (babel::AccountManagerException & e)
    {
      return false;
    }
  return this->_server.getAccountManager().getAccountByLogin(login_req).addContact(login);
}

bool babel::AccountManager::removeContact(const std::string &login_req, const std::string &login)
{
  return this->_server.getAccountManager().getAccountByLogin(login_req).removeContact(login);
}