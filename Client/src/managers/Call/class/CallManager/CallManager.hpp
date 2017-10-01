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
            bool                                    _isOwner;

		public:
            const bool&                             isOwner(void) const;
			babel::BabelClientManager&				getRoot(void);
			const babel::BabelClientManager&		getRoot(void) const;
			const babel::Call&						getCurrentcall(void) const;
            babel::Call&							getCurrentCall(void);
            void                                    setOwner(const bool);

		public:
            const babel::Status                     leaveCall(void);
            const babel::Status                     addNewParticipant(const babel::CallTunnel&);

            void                                    updateCurrentCallParticipants(const std::unordered_map<std::string, babel::CallTunnel>&);
			void									resetCurrentCall(void);
            void									removeParticipant(const std::string&);
	};
}

#endif // !BABEL_CALLMANAGER_HPP_
