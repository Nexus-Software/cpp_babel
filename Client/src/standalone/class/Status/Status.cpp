#include <iostream>
#include "Status.hpp"

babel::Status::Status(const int code, const std::string& note)
:
	_code(code),
	_anotation(note)
{
	std::cout << "Status created with code " << code << std::endl;
}

babel::Status::~Status() {
	std::cout << "Status destructed" << std::endl;
}

const int& babel::Status::getCode(void) const {
	return this->_code;
}

const std::string& babel::Status::getAnotation(void) const {
	return this->_anotation;
}

void babel::Status::anote(const std::string& note) {
	this->_anotation = note;
}

std::ostream& operator<<(std::ostream& os, const babel::Status& st)
{
	os << "[" << __DATE__ << " - " << __TIME__ << "]: Code " << st.getCode() << " catched (" << st.getAnotation() << ")";
	return os;
}