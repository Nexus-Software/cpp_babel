#ifndef BABEL_CALL_HPP_
# define BABEL_CALL_HPP_

#include <vector>
#include <iostream>
#include "Contact.hpp"
#include "Status.hpp"

namespace babel {
	class Call
	{
		public:
			Call();
			Call(const babel::Call&);
			virtual ~Call();

		private:
			std::vector<std::string>		_participants;
			bool							_isActive;
			bool							_isMute;

		public:
			const std::vector<std::string>&		getParticipants(void) const;
			std::vector < std::string>&			getParticipants(void);
			const bool							getActivity(void) const;
			const bool							isMute(void) const;

			void								setActivity(const bool);
			void								mute(void);
			void								unmute(void);
			void								reset(void);
			const std::vector<std::string>&		updateParticipantsList(const std::vector<std::string>&);
		
		private:
			void setMute(const bool);
	};
}

std::ostream& operator<<(std::ostream& os, const babel::Call&);

#endif // !BABEL_CALL_HPP_
