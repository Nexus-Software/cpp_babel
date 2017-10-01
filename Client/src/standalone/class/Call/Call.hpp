#ifndef BABEL_CALL_HPP_
# define BABEL_CALL_HPP_

#include <unordered_map>
#include <iostream>
#include "Contact.hpp"
#include "Status.hpp"

namespace babel {

    struct CallTunnel
      {
        CallTunnel(std::string _login, std::string _ip, unsigned int _port): login(_login), ip(_ip), port(_port) {}

        std::string         login;
        std::string         ip;
        unsigned int        port;
      };

	class Call
	{
		public:
			Call();
			Call(const babel::Call&);
			virtual ~Call();

		private:
            std::unordered_map<std::string, babel::CallTunnel>          _participants;
            bool                                                        _isActive;
            bool                                                        _isMute;
            std::uint32_t                                               _idConv;

		public:
            void                                                        setIdConv(std::uint32_t const idConv);

            const std::unordered_map<std::string, babel::CallTunnel>    &getParticipants(void) const;
            std::unordered_map<std::string, babel::CallTunnel>			&getParticipants(void);
            const bool                                                  getActivity(void) const;
            const std::uint32_t                                         &getIdConv(void) const;

            const bool                                                  isMute(void) const;

            void                                                        setActivity(bool const);
            void                                                        mute(void);
            void                                                        unmute(void);
            void                                                        reset(void);
            const std::unordered_map<std::string, babel::CallTunnel>    &updateParticipantsList(std::unordered_map<std::string, babel::CallTunnel> const&);
			void														removeParticipants(const std::string&);
		
		private:
			void setMute(const bool);
	};
}

std::ostream& operator<<(std::ostream& os, const babel::Call&);

#endif // !BABEL_CALL_HPP_
