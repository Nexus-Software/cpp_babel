#ifndef BABEL_BABELCLIENTMANAGER_HPP_
# define BABEL_BABELCLIENTMANAGER_HPP_

#include "GlobalMediaManager.hpp"
#include "UIManager.hpp"
#include "NetworkManager.hpp"
#include "ContactManager.hpp"
#include "Call.hpp"
#include "Status.hpp"

namespace babel {
	class BabelClientManager
	{
		public:
			BabelClientManager();
			~BabelClientManager();

		private:
			babel::GlobalMediaManager	_media;
			babel::UIManager			_ui;
			babel::NetworkManager		_network;
			babel::ContactManager		_contact;
			babel::Call					_currentCall;

		public:
			const babel::GlobalMediaManager&	getMedia(void)			const;
			const babel::UIManager&				getUI(void)				const;
			const babel::NetworkManager&		getNetwork(void)		const;
			const babel::ContactManager&		getContact(void)		const;
			const babel::Call&					getCurrentCall(void)	const;

		public:
			const babel::Status run(void);
	};
}

#endif // !BABEL_BABELCLIENTMANAGER_HPP_
