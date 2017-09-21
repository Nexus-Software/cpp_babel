#ifndef BABEL_ICOMMUNICATION_HPP
# define BABEL_ICOMMUNICATION_HPP

namespace babel {
	class ICommunication
	{
		public:
			virtual ~ICommunication();

		private:
			void send()			= 0;
			void get()			= 0;
			void pingHost()		= 0;
	};
}

#endif // !BABEL_ICOMMUNICATION_HPP
