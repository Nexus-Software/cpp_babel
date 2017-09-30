#include "Codec.hpp"
#include "Audio.hpp"

babel::Codec::Codec(void)
{
	this->_encoder = opus_encoder_create(SAMPLE_RATE, NUM_CHANNELS, OPUS_APPLICATION_VOIP, &this->_err);
	if (this->_err < 0)
		std::cout << "error encoder create: " << opus_strerror(this->_err) << std::endl;
	this->_decoder = opus_decoder_create(SAMPLE_RATE, NUM_CHANNELS, &this->_err);
	if (this->_err < 0)
		std::cout << "error decoder create: " << opus_strerror(this->_err) << std::endl;
	opus_encoder_ctl(this->_encoder, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
}

babel::Codec::~Codec(void)
{
	opus_encoder_destroy(this->_encoder);
	opus_decoder_destroy(this->_decoder);
}

EncodedData const   babel::Codec::Encode(std::vector<float> const &encryptMe)
{
	this->_back.data.clear();
	this->_back.data.resize(MAX_PACKET);
	if ((this->_back.lenght = opus_encode_float(this->_encoder, encryptMe.data(), encryptMe.size() / NUM_CHANNELS, this->_back.data.data(), MAX_PACKET)) < 0)
	{
		std::cerr << "Error: " << opus_strerror(this->_back.lenght) << std::endl;
		this->_back.lenght = 0;
	}
	return (this->_back);
}

void						babel::Codec::Decode(EncodedData decryptMe, std::vector<float> &sample) const
{
	int						frameSize;

	sample.resize(MAX_FRAME_SIZE * NUM_CHANNELS);
	if ((frameSize = opus_decode_float(this->_decoder, decryptMe.data.data(), decryptMe.lenght, sample.data(), MAX_FRAME_SIZE, 0)) < 0)
		std::cerr << "Error: " << frameSize << std::endl;
	else
		sample.resize(frameSize * NUM_CHANNELS);
}