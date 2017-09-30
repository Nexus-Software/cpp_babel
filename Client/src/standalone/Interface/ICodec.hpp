#ifndef I_CODEC_HPP
# define I_CODEC_HPP

#include "opus_multistream.h"
#include "opus_defines.h"
#include "opus_custom.h"
#include "opus_types.h"
#include "opus.h"
#include <vector>

struct                        EncodedData
 {
	opus_int32                  lenght;
	std::vector<unsigned char>  data;
	
		EncodedData() {};
	EncodedData(opus_int32 l, std::vector<unsigned char> &d) : lenght(l), data(d) {};
	EncodedData &operator=(const EncodedData &other)
		 {
		if (this != &other)
			 {
			this->lenght = other.lenght;
			this->data.clear();
			for (unsigned int i = 0; i < other.data.size(); ++i)
				 this->data.push_back(other.data.at(i));
			}
		}
	};

class ICodec
 {
	public:
		virtual EncodedData const   Encode(std::vector<float> const &) = 0;
		virtual void                Decode(EncodedData, std::vector<float> &) const = 0;
};

#endif