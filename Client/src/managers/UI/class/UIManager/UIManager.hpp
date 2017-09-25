#ifndef BABEL_UIMANAGER_HPP_
# define BABEL_UIMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <QApplication>
#include "Status.hpp"
#include "addcontactdiag.h"
#include "customnotificationdiag.h"
#include "logindiag.h"
#include "mainwindow.h"
#include "receivecalldiag.h"
#include "signupdiag.h"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class UIManager
	{
		public:
			UIManager(babel::BabelClientManager&);
            ~UIManager();

            babel::Status const                                                 showWindow(std::string const& windowName);
            babel::Status const                                                 hideWindow(std::string const& windowName);

            babel::Status const                                                 start();

            babel::BabelClientManager                                           &getRoot();
            babel::BabelClientManager const                                     &getRoot() const;
            std::unordered_map<std::string, std::shared_ptr<QWidget>>           &getWindowList();

		private:
			babel::BabelClientManager&											_root;
            std::unordered_map<std::string, std::shared_ptr<QWidget>>           _windowList;

	};
}

#endif // !BABEL_UIMANAGER_HPP_
