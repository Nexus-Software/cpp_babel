#include <iostream>
#include "Contact.hpp"

babel::Contact::Contact()
{
	std::cout << "Contact created" << std::endl;
}

babel::Contact::Contact(const babel::Contact& item)
	:
	_login(item.getLogin()),
	_status(item.getStatus())
{

}

babel::Contact::Contact(std::string const& login, bool const status) :
    _login(login),
    _status(status)
{

}

babel::Contact::~Contact()
{
	std::cout << "Contact destructed" << std::endl;
}

const std::string & babel::Contact::getLogin() const
{
	return this->_login;
}

std::string babel::Contact::getLogin()
{
	return this->_login;
}

const bool babel::Contact::getStatus() const
{
	return this->_status;
}

bool babel::Contact::getStatus()
{
	return this->_status;
}

void babel::Contact::setLogin(const std::string & newLogin)
{
	this->_login = newLogin;
}

void babel::Contact::setStatus(const bool status)
{
	this->_status = status;
}

babel::Contact& babel::Contact::operator=(const Contact& item)
{
	if (this != &item) {
		this->setLogin(item.getLogin());
		this->setStatus(item.getStatus());
	}
	return *this;
}
