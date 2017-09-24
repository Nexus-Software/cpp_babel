/*
** Account.cpp for Server in /home/enguerrand/delivery/Server/Account.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 23:44:28 2017 Enguerrand Allamel
** Last update dim. sept. 24 23:44:28 2017 Enguerrand Allamel
*/

#include "Account.hpp"

babel::Account::Account(std::string login, std::string password):
	_login(login),
	_password(password),
	_isOnline(false)
{
}

babel::Account::~Account()
{

}

const std::string &babel::Account::getLogin() const
{
  return this->_login;
}

const std::string &babel::Account::getPassword() const
{
  return this->_password;
}

bool babel::Account::getIsOnline() const
{
  return this->_isOnline;
}

const std::unordered_map<std::string, babel::Account> &babel::Account::getContactList() const
{
  return this->_contactList;
}

void babel::Account::setPassword(const std::string &password)
{
  this->_password = password;
}

void babel::Account::setIsOnline(bool isOnline)
{
  this->_isOnline = isOnline;
}
