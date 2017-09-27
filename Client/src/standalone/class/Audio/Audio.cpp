//
// Made by Marco
//

#include "Audio.hpp"


/////////////////////////////////////////////
//---------CONSTRUCTOR-DESTRUCTOR----------//
/////////////////////////////////////////////

babel::Audio::Audio(void)
{
}

babel::Audio::~Audio(void)
{
}

/////////////////////////////////////////////
//---------INITIALIZOR-TERMINATOR----------//
/////////////////////////////////////////////

int		babel::Audio::initialize(void)
{
	if ((this->_err = Pa_Initialize()) != paNoError)
	{
		std::cerr << "Error: Initialization failed: " << Pa_GetErrorText(this->_err) << std::endl;
		return (1);
	}
	return (0);
}

int		babel::Audio::terminate(void)
{
	Pa_Terminate();
	return (0);
}

/////////////////////////////////////////////
//---------------START-STOP----------------//
/////////////////////////////////////////////

int		babel::Audio::startStream(bool record, bool difuse)
{
	PaStreamParameters  inputParameters;
	PaStreamParameters  outputParameters;
	float				*sample;

	this->_record = this->_difuse = false;

	if (record)
	{
		if ((inputParameters.device = Pa_GetDefaultInputDevice()) == paNoDevice)
		{
			std::cerr << "Error: No default input device." << std::endl;
			return (1);
		}
		inputParameters.channelCount = NUM_CHANNELS;
		inputParameters.sampleFormat = paFloat32;
		inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
		inputParameters.hostApiSpecificStreamInfo = NULL;
	}
	
	if (difuse)
	{
		if ((outputParameters.device = Pa_GetDefaultOutputDevice()) == paNoDevice)
		{
			std::cerr << "Error: No default output device." << std::endl;
			return (1);
		}

		outputParameters.channelCount = NUM_CHANNELS;
		outputParameters.sampleFormat = paFloat32;
		outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;
	}

	if ((sample = new float[NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS]) == NULL)
	{
		std::cerr << "Error: Malloc failed." << std::endl;
		return (1);
	}

	if (record && difuse)
		this->_err = Pa_OpenStream(&this->_stream, &inputParameters, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
	else if (record && !difuse)
		this->_err = Pa_OpenStream(&this->_stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
	else if (difuse && !record)
		this->_err = Pa_OpenStream(&this->_stream, NULL, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
	else
	{
		std::cerr << "Warning: Stream not open: Please select at least one of the 2 choices." << std::endl;
		delete sample;
		return (1);
	}

	if (this->_err != paNoError)
	{
		std::cerr << "Error: An error occured when opening the stream." << std::endl;
		delete sample;
		return (1);
	}

	if ((this->_err = Pa_StartStream(this->_stream)) != paNoError)
	{
		std::cerr << "Error: An error occured when starting the stream." << std::endl;
		delete sample;
		return (1);
	}

	if (this->_recordedData)
		delete this->_recordedData;
	this->_recordedData = sample;
	this->_record = record;
	this->_difuse = difuse;
	this->_sizeRecordedData = NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
	return (0);
}

int		babel::Audio::stopStream(void)
{
	if (this->_stream == NULL)
	{
		std::cerr << "Error: An error occured when closing the stream: No Stream Opened" << std::endl;
		return (1);
	}

	if ((this->_err = Pa_CloseStream(this->_stream)) != paNoError)
	{
		std::cerr << "Error: An error occured when closing the stream: " << Pa_GetErrorText(this->_err) << std::endl;
		return (1);
	}

	this->_record = this->_difuse = false;
	if (this->_recordedData)
		delete this->_recordedData;
	if (this->_toPlayData)
		delete this->_toPlayData;
	this->_sizeRecordedData = this->_sizeToPlayData = 0;
	return (0);
}

/////////////////////////////////////////////
//-----------------GETTER------------------//
/////////////////////////////////////////////

float	*babel::Audio::getRecord(void) const
{
	return (this->_recordedData);
}

int		babel::Audio::getRecordSize(void) const
{
	return (this->_sizeRecordedData);
}

int		babel::Audio::getPlayBackSize(void) const
{
	return (this->_sizeToPlayData);
}

/////////////////////////////////////////////
//-----------------SETTER------------------//
/////////////////////////////////////////////

void	babel::Audio::setPlayBack(float *playMe, int size)
{
	this->_sizeToPlayData = size;
	this->_toPlayData = playMe;
}

/////////////////////////////////////////////
//-----------------CLEANER-----------------//
/////////////////////////////////////////////

void	babel::Audio::cleanRecord(void)
{
	for (auto i = 0; i < this->_sizeRecordedData; i++)
		this->_recordedData = 0;
}

/////////////////////////////////////////////
//-----------------ACTION------------------//
/////////////////////////////////////////////

int		babel::Audio::run(void)
{
	if ((this->_err = Pa_IsStreamActive(this->_stream)) != 1)
	{
		std::cerr << "Error: Can't run the stream: Stream inactive." << std::endl;
		return (1);
	}

	if (this->_record)
	{
		if ((this->_err = Pa_ReadStream(this->_stream, this->_recordedData, this->_sizeRecordedData / NUM_CHANNELS)) != paNoError)
		{
			std::cerr << "Error: An error occured when recording stream: " << Pa_GetErrorText(this->_err) << std::endl;
			return (1);
		}
	}

	if (this->_difuse)
	{
		if ((this->_err = Pa_WriteStream(this->_stream, this->_toPlayData, this->_sizeToPlayData / NUM_CHANNELS)) != paNoError)
		{
			std::cerr << "Error: An error occured when reading stream: " << Pa_GetErrorText(this->_err) << std::endl;
			return (1);
		}
	}
	return (0);
}