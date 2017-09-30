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
			bool 		playSound(B_SAMPLE);
			B_SAMPLE 	recordSound(void);
			bool 		encodeSound(void);
			bool 		decodeSound(void);
			void 		setAudioStreamState(bool);


	};
}

#endif // !BABEL_GLOBALMEDIAMANAGER_HPP_
