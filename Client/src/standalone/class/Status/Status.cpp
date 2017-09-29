#include <iostream>
#include "Status.hpp"

babel::Status::Status(const int code, const std::string& note)
:
	_code(code),
    _annotation(note)
{
}

babel::Status::Status(babel::Status const& status) :
    _code(status.getCode()),
    _annotation(status.getAnnotation())
{

}

babel::Status::~Status() {

}

const int           &babel::Status::getCode(void) const {
    return this->_code;
}

const std::string   &babel::Status::getAnnotation(void) const {
    return this->_annotation;
}

int                 &babel::Status::getCode(void) {
    return this->_code;
}

std::string         &babel::Status::getAnnotation(void) {
    return this->_annotation;
}

void                babel::Status::setCode(const int code) {
    this->_code = code;
}

void                babel::Status::setAnnotation(std::string const& note) {
    this->_annotation = note;
}

std::ostream& operator<<(std::ostream& os, const babel::Status& st)
{
    os << "[" << __DATE__ << " - " << __TIME__ << "]: Code " << st.getCode() << " catched (" << st.getAnnotation() << ")";
	return os;
}

babel::Status &babel::Status::operator=(babel::Status const& status)
{
    this->setCode(status.getCode());
    this->setAnnotation(status.getAnnotation());
    return (*this);
}
