#ifndef BABEL_UIMANAGER_HPP_
# define BABEL_UIMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include "IDialog.hpp"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class UIManager
	{
		public:
			UIManager(babel::BabelClientManager&);
			~UIManager();

		private:
			babel::BabelClientManager&											_root;
			std::unordered_map<std::string, std::shared_ptr<babel::IDialog>>	_dialogList;

	};
}

#endif // !BABEL_UIMANAGER_HPP_
