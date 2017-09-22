#ifndef BABEL_STATUS_HPP_
# define BABEL_STATUS_HPP_

#include <iostream>
#include <string>

namespace babel {
	class Status
	{
		public:
			Status(int code, const std::string& note = "No anotation assigned");
			~Status();

		private:
			const int		_code;
			std::string		_anotation;


		public:
			const int& getCode(void) const;
			const std::string& getAnotation(void) const;

			void anote(const std::string& note);


	};
}

std::ostream& operator<<(std::ostream& os, const babel::Status& st);

#endif // !BABEL_STATUS_HPP_
