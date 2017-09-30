//
// Made by Marco
//

#include "Audio.hpp"

/////////////////////////////////////////////
//---------CONSTRUCTOR-DESTRUCTOR----------//
/////////////////////////////////////////////

babel::Audio::Audio(void)
{
	this->initialize();
}

babel::Audio::~Audio(void)
{
	this->terminate();
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
	PaStreamParameters		inputParameters;
	PaStreamParameters		outputParameters;

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
		inputParameters.suggestedLatency = LATENCY_CONSTANT * Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
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
		outputParameters.suggestedLatency = LATENCY_CONSTANT * Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;
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
		return (1);
	}

	if (this->_err != paNoError)
	{
		std::cerr << "Error: An error occured when opening the stream." << std::endl;
		return (1);
	}

	if ((this->_err = Pa_StartStream(this->_stream)) != paNoError)
	{
		std::cerr << "Error: An error occured when starting the stream." << std::endl;
		return (1);
	}

	this->_record = record;
	this->_difuse = difuse;
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
	return (0);
}

/////////////////////////////////////////////
//-----------------CLEANER-----------------//
/////////////////////////////////////////////

void	babel::Audio::cleanRecord(void)
{
	this->_recordedData = {0};
}

/////////////////////////////////////////////
//-----------------ACTION------------------//
/////////////////////////////////////////////

B_SAMPLE 	babel::Audio::record()
{
	B_SAMPLE buffer(FRAME_SIZE);

	if ((this->_err = Pa_IsStreamActive(this->_stream)) != 1)
	{
		std::cerr << "Error: Can't run the stream: Stream inactive." << std::endl;
		return {0};
	}
	
	if ((this->_err = Pa_ReadStream(this->_stream, buffer.data(), FRAME_SIZE / NUM_CHANNELS)) != paNoError)
	{
		std::cerr << "Error: An error occured when recording stream: " << Pa_GetErrorText(this->_err) << std::endl;
		return {0};
	}

	return buffer;
}

bool 	babel::Audio::play(B_SAMPLE audio)
{
	if ((this->_err = Pa_IsStreamActive(this->_stream)) != 1)
	{
		std::cerr << "Error: Can't run the stream: Stream inactive." << std::endl;
		return false;
	}
	
	if ((this->_err = Pa_WriteStream(this->_stream, audio.data(), FRAME_SIZE / NUM_CHANNELS)) != paNoError)
	{
		std::cerr << "Error: An error occured when reading stream: " << Pa_GetErrorText(this->_err) << std::endl;
		return false;
	}
	return true;
}