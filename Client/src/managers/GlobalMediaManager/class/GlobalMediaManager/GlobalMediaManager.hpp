#ifndef BABEL_GLOBALMEDIAMANAGER_HPP_
# define BABEL_GLOBALMEDIAMANAGER_HPP_

#include "AudioManager.hpp"

namespace babel {
	class BabelClientManager;
} // babel

namespace babel {
	class GlobalMediaManager
	{
		public:
			GlobalMediaManager(babel::BabelClientManager&);
			~GlobalMediaManager();

		private:
			babel::BabelClientManager&	_root;
			babel::AudioManager 		_audioManager;

		public:
			babel::BabelClientManager& getRoot(void) const;

		// Sound methods
		public:
			bool 	playSound(void);
			bool 	getSound(void);
			bool 	encodeSound(void);
			bool 	decodeSound(void);


	};
}

#endif // !BABEL_GLOBALMEDIAMANAGER_HPP_
