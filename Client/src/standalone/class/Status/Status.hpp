#ifndef BABEL_STATUS_HPP_
# define BABEL_STATUS_HPP_

#include <iostream>
#include <string>

namespace babel {
	class Status
	{
        public:
            Status(int code, const std::string& note = "No annotation assigned");
            Status(Status const& status);
			~Status();

		private:
            int             _code;
            std::string		_annotation;


        public:
            const int           &getCode(void) const;
            const std::string   &getAnnotation(void) const;
            int                 &getCode(void);
            std::string         &getAnnotation(void);

            void                setCode(const int code);
            void                setAnnotation(const std::string& note);

            Status              &operator=(Status const& status);
	};
}

std::ostream    &operator<<(std::ostream& os, const babel::Status& st);
#endif // !BABEL_STATUS_HPP_
