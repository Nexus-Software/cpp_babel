#ifndef BABEL_CODEC_HPP_
# define BABEL_CODEC_HPPç

#include "ICodec.hpp"

namespace babel {
	class Codec : public ICodec
	{
		private:
			OpusEncoder*	_encoder;
			OpusDecoder*	_decoder;
			int				_err;
			EncodedData		_back;

		public:
			explicit Codec(void);

			virtual ~Codec(void);

		public:
			virtual EncodedData const	Encode(std::vector<float>const&);
			virtual void                Decode(EncodedData, std::vector<float> &) const;
	};
}

#endif // !BABEL_CODEC_HPP_
