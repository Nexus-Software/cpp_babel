#ifndef BABEL_AUDIOMANAGER_HPP_
# define BABEL_AUDIOMANAGER_HPP_

#include <thread>
#include "Codec.hpp"
#include "Audio.hpp"

namespace babel {
	class GlobalMediaManager;
} // babel

namespace babel {
	class AudioManager
	{
		public:
			AudioManager(babel::GlobalMediaManager&);
			~AudioManager();

		private:
			babel::GlobalMediaManager& 		_parent;
			babel::Audio					_audio;
			bool							_run;
			std::shared_ptr<std::thread>	_thread;

		public:
			babel::GlobalMediaManager&	getParent(void) const;
			bool 						playSound(B_SAMPLE);
			B_SAMPLE					recordSound(void);
			bool 						encodeSound(void);
			bool 						decodeSound(void);
			void 						setStreamState(bool);
	};
}

#endif // !BABEL_AUDIOMANAGER_HPP_
