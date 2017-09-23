#ifndef BABEL_CALLMANAGER_HPP_
#define BABEL_CALLMANAGER_HPP_

#include <iostream>
#include <vector>
#include "Call.hpp"
#include "Status.hpp"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class CallManager
	{
		public:
			CallManager(babel::BabelClientManager&);
			~CallManager();

		private:
			babel::BabelClientManager&	_root;
			babel::Call					_currentCall;
			std::vector<babel::Call>	_callHistory;

		public:
			babel::BabelClientManager&				getRoot(void);
			const babel::BabelClientManager&		getRoot(void) const;
			const babel::Call&						getCurrentcall(void) const;
			babel::Call&							getCurrentCall(void);
			const std::vector<babel::Call>&			getCallHistory(void) const;
			std::vector<babel::Call>&				getCallHistory(void);

		public:
			const babel::Status leaveCall(void);
			const babel::Status addNewParticipant(const std::string&);
			const babel::Status joinCall(const std::vector<std::string>&);
			const std::vector<std::string>& updateCurrentCallParticipants(void);

		private:
			void archiveCurrentCall(void);
			void resetCurrentCall(void);


	};
}

#endif // !BABEL_CALLMANAGER_HPP_
