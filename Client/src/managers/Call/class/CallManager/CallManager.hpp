#ifndef BABEL_CALLMANAGER_HPP_
#define BABEL_CALLMANAGER_HPP_

#include <iostream>
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
            babel::BabelClientManager&              _root;
            babel::Call                             _currentCall;

		public:
			babel::BabelClientManager&				getRoot(void);
			const babel::BabelClientManager&		getRoot(void) const;
			const babel::Call&						getCurrentcall(void) const;
            babel::Call&							getCurrentCall(void);

		public:
            const babel::Status                     leaveCall(void);
            const babel::Status                     addNewParticipant(const std::string&);
            const babel::Status                     joinCall(const std::unordered_map<std::string, babel::CallTunnel>&);
            const std::unordered_map<std::string, babel::CallTunnel>    &updateCurrentCallParticipants(void);

        private:
			void resetCurrentCall(void);


	};
}

#endif // !BABEL_CALLMANAGER_HPP_
