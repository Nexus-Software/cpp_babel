#ifndef BABEL_CONTACT_EXCEPTION_HPP_
#define BABEL_CONTACT_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace babel {
	class ContactException : public std::exception
	{
		protected:
			std::string _msg;
		public:

			explicit ContactException(const char* message):			_msg(message)	{}
			explicit ContactException (const std::string& message):	_msg(message)	{}
	
			virtual ~ContactException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !BABEL_CONTACT_EXCEPTION_HPP_