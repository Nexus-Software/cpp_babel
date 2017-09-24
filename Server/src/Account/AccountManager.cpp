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
  this->_accountList.insert(std::pair<std::string, Account>(login, Account(login, password)));
  //Todo: Throw error if fail insert
  return true;
}

bool babel::AccountManager::remove(std::string login)
{
  this->_accountList.erase(login);
  //Todo: Throw error if fail erase
  return true;
}

babel::Account babel::AccountManager::getAccountByLogin(const std::string login)
{
  std::unordered_map<std::string, Account>::iterator it;

  if ((it = this->_accountList.find(login)) != this->_accountList.end())
    return (*it).second;
  //Todo: Throw error (is not good yet)
  return babel::Account("", "");
}

babel::Account const babel::AccountManager::getAccountByLogin(const std::string login) const
{
  std::unordered_map<std::string, Account>::const_iterator it;

  if ((it = this->_accountList.find(login)) != this->_accountList.end())
    return (*it).second;
  //Todo: Throw error (is not good yet)
  return babel::Account("", "");
}

const std::unordered_map<std::string, babel::Account> &babel::AccountManager::getAccountList() const
{
  return this->_accountList;
}


