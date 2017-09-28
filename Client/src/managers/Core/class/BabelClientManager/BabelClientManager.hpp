#ifndef BABEL_BABELCLIENTMANAGER_HPP_
# define BABEL_BABELCLIENTMANAGER_HPP_

#include "GlobalMediaManager.hpp"
#include "UIManager.hpp"
#include "NetworkManager.hpp"
#include "ContactManager.hpp"
#include "CallManager.hpp"
#include "Status.hpp"

namespace babel {
	class BabelClientManager
	{
		public:
            BabelClientManager(int argc, char **argv);
			~BabelClientManager();

        private:
			QApplication                _app;
			babel::GlobalMediaManager	_media;
			babel::UIManager			_ui;
			babel::NetworkManager		_network;
			babel::ContactManager		_contact;
			babel::CallManager			_call;
			const int                   _argc;
			char                        **_argv;

        public:
			const babel::GlobalMediaManager&	getMedia(void)			const;
			const babel::UIManager&				getUI(void)				const;
			const babel::NetworkManager&		getNetwork(void)		const;
			const babel::ContactManager&		getContact(void)		const;
			const babel::CallManager&			getCall(void)			const;

			babel::GlobalMediaManager&          getMedia(void);
			babel::UIManager&                   getUI(void);
			babel::NetworkManager&              getNetwork(void);
			babel::ContactManager&              getContact(void);
            babel::CallManager&                 getCall(void);
			const int                           getArgc(void)			const;
			char                                **getArgv(void)			const;
			QApplication                        &getApp(void);
			const QApplication                  &getApp(void)			const;

			const int run(void);
	};
}

#endif // !BABEL_BABELCLIENTMANAGER_HPP_
