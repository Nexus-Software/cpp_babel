#include <iostream>
#include <algorithm>
#include "ContactManager.hpp"

babel::ContactManager::ContactManager(babel::BabelClientManager& ancestor)
:
	_root(ancestor)
{
	std::cout << "ContactManager created" << std::endl;
}

babel::ContactManager::~ContactManager()
{
	std::cout << "ContactManager destructed" << std::endl;
}

const babel::BabelClientManager & babel::ContactManager::getRoot() const
{
	return this->_root;
}

babel::BabelClientManager & babel::ContactManager::getRoot()
{
	return this->_root;
}

const babel::Contact & babel::ContactManager::getUser() const
{
	return this->_user;
}

babel::Contact & babel::ContactManager::getUser()
{
	return this->_user;
}

const std::vector<babel::Contact>& babel::ContactManager::getContactList() const
{
	return this->_contactList;
}

std::vector<babel::Contact>& babel::ContactManager::getContactList()
{
	return this->_contactList;
}

void babel::ContactManager::setContactList(const std::vector<babel::Contact>& newList)
{
	this->_contactList = newList;
}

void babel::ContactManager::setUser(const babel::Contact& newUser)
{
	this->_user = newUser;
}

const babel::Contact & babel::ContactManager::getContactByLogin(const std::string & login) const
{
	auto it = std::find_if(this->_contactList.begin(), this->_contactList.end(), [&](auto obj) { return login == obj.getLogin(); });
	if (it == this->_contactList.end())
		throw ContactException("Unknown login");
	else
		return *it;
}

babel::Contact & babel::ContactManager::getContactByLogin(const std::string & login)
{
	auto it = std::find_if(this->_contactList.begin(), this->_contactList.end(), [&](auto obj) { return login == obj.getLogin(); });
	if (it == this->_contactList.end())
		throw ContactException("Unknown login");
	else
		return *it;
}

void babel::ContactManager::updateContactList(const std::vector<babel::Contact>& list)
{
	this->_contactList = list;
}

const babel::Status & babel::ContactManager::addContactByLogin(const std::string &)
{
	// TODO : ADDING NETWORK CALL HERE
	return babel::Status(0, "Contact added");
}

const babel::Status & babel::ContactManager::removeContactByLogin(const std::string &)
{
	// TODO : Call network implementation of removeContact here
	return babel::Status(0, "Contact removed successfully");
}
