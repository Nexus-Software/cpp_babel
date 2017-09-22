#ifndef BABEL_CONTACT_HPP_
# define BABEL_CONTACT_HPP_

#include <string>
#include "ContactException.hpp"

namespace babel {
	class Contact
	{
		public:
			Contact();
			Contact(const babel::Contact&);
			Contact& operator=(const Contact&);
			virtual ~Contact();

		private:
			std::string		_login;
			bool			_status;

		public:
			const std::string& getLogin() const;
			std::string  getLogin();

			const bool getStatus() const;
			bool getStatus();

			void setLogin(const std::string&);
			void setStatus(const bool);

	};
}

#endif // !BABEL_CALL_HPP_
