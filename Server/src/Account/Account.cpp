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

const std::vector<std::string> &babel::Account::getContactList() const
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

bool babel::Account::addContact(const std::string &login)
{
  if (std::find(this->_contactList.begin(), this->_contactList.end(), login) != this->_contactList.end())
    return false;
  this->_contactList.push_back(login);
  return true;
}

bool babel::Account::removeContact(const std::string &login)
{
  if (std::find(this->_contactList.begin(), this->_contactList.end(), login) == this->_contactList.end())
    return false;
  auto it = std::find(this->_contactList.begin(), this->_contactList.end(), login);
  this->_contactList.erase(it);
  return true;
}
