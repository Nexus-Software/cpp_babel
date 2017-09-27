//
// Made by Marco
//

#include "Audio.hpp"

int						recordMe()
{
	PaStreamParameters  inputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	SAMPLE				*data;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;
	SAMPLE              max, val;
	double              average;

	totalFrames = NUM_SECONDS * SAMPLE_RATE;
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data = (SAMPLE *)malloc(numBytes);

	if (data == NULL)
	{
		printf("Could not allocate record array.\n");
		goto done;
	}

	for (i = 0; i<numSamples; i++)
		data[i] = 0;

	err = Pa_Initialize();
	if (err != paNoError)
		goto done;

	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device == paNoDevice)
	{
		std::cout << "Error: No default input device." << std::endl;
		goto done;
	}

	inputParameters.channelCount = 2;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	/* Record some audio. -------------------------------------------- */
	err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);

	if (err != paNoError)
		goto done;

	err = Pa_StartStream(stream);
	if (err != paNoError)
		goto done;

	std::cout << "\n=== Now recording!! Please speak into the microphone. ===\n";

	int		count = 0;
	FILE	*fd;
	fd = fopen("recorded.raw", "wb");

	while ((err = Pa_IsStreamActive(stream)) == 1 && count < 3)
	{
		std::cout << "-";
		Pa_ReadStream(stream, data, totalFrames);
		if (fd != NULL)
			fwrite(data, sizeof(SAMPLE), numSamples, fd);
		count += 1;
	}
	std::cout << "---------------------------| finish\n";

	if (fd != NULL)
		fclose(fd);

	if (err < 0)
		goto done;

	err = Pa_CloseStream(stream);
	if (err != paNoError)
		goto done;

done:
	Pa_Terminate();
	if (data)
		free(data);
	if (err != paNoError)
	{
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;
	}
	return err;
}

int						playbackMe()
{
	PaStreamParameters  inputParameters, outputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	SAMPLE				*data;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;
	SAMPLE              max, val;
	double              average;


	totalFrames = NUM_SECONDS * SAMPLE_RATE;
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data = (SAMPLE *)malloc(numBytes);

	if (data == NULL)
	{
		printf("Could not allocate record array.\n");
		goto done;
	}

	for (i = 0; i<numSamples; i++)
		data[i] = 0;

	err = Pa_Initialize();
	if (err != paNoError)
		goto done;

	// Playback recorded data.  --------------------------------------------

	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice)
	{
		fprintf(stderr, "Error: No default output device.\n");
		goto done;
	}

	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(&stream, NULL, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL);
	if (err != paNoError)
		goto done;

	if (stream)
	{
		err = Pa_StartStream(stream);
		if (err != paNoError)
			goto done;

		printf("\n=== Now playing back. ===\n"); fflush(stdout);
		std::cout << "Waiting for playback to finish.\n";

		FILE	*fd;
		fd = fopen("recorded.raw", "r");

		if (fd == NULL)
		{
			fclose(fd);
			std::cout << "fd close" << std::endl;
			goto done;
		}

		while (fread(data, sizeof(SAMPLE), numSamples, fd))
		{
			std::cout << "-";
			if ((err = Pa_IsStreamActive(stream)) == 1)
				Pa_WriteStream(stream, data, totalFrames);
		}
		if (err < 0)
			goto done;

		err = Pa_CloseStream(stream);
		if (err != paNoError)
			goto done;

		std::cout << "Done" << std::endl;
	}

done:
	Pa_Terminate();
	if (data)
		free(data);
	if (err != paNoError)
	{
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;
	}
	return err;
}