//
// Made by Marco
//

#include "Audio.hpp"

int						record(void)
{
	PaStreamParameters  inputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;
	SAMPLE              max, val;
	double              average;

	std::cout << "RECORD" << std::endl;

	data.maxIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data.recordedSamples = (SAMPLE *)malloc(numBytes); /* From now on, recordedSamples is initialised. */
	data.run = true;
	data.writeIndex = 0;
	data.readIndex = 0;
	data.swap = false;
	data.maxIndex *= NUM_CHANNELS;
	if (data.recordedSamples == NULL)
	{
		printf("Could not allocate record array.\n");
		goto done;
	}
	for (i = 0; i<numSamples; i++) data.recordedSamples[i] = 0;

	err = Pa_Initialize();
	if (err != paNoError) goto done;

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default input device.\n");
		goto done;
	}
	inputParameters.channelCount = 2;                    /* stereo input */
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	/* Record some audio. -------------------------------------------- */
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		NULL,                  /* &outputParameters, */
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		recordCallback,
		&data);
	if (err != paNoError) goto done;

	err = Pa_StartStream(stream);
	if (err != paNoError) goto done;
	printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

	max = 0;
	FILE	*fd;
	fd = fopen("recorded.raw", "wb");

	while ((err = Pa_IsStreamActive(stream)) == 1)
	{
		Pa_Sleep(1000);
		if (extractFromList(&data, distanceToWr(data.writeIndex, data.readIndex, data.swap, data.maxIndex), fd) != 0)
			std::cout << "Error when writing in file" << std::endl;
		if (max > 15)
			data.run = false;
		//sprintf("index = %d\n", data.writeIndex); fflush(stdout);
		max += 1;
	}
	if (extractFromList(&data, distanceToWr(data.writeIndex, data.readIndex, data.swap, data.maxIndex), fd) != 0)
		std::cout << "Error when writing in file" << std::endl;
	if (fd != NULL)
	{
		max = 0;
		fwrite(&max, sizeof(int), 1, fd);
		fclose(fd);
	}

	if (err < 0) goto done;

	err = Pa_CloseStream(stream);
	if (err != paNoError) goto done;

	/* Measure maximum peak amplitude. */
	max = 0;
	average = 0.0;
	for (i = 0; i<numSamples; i++)
	{
		val = data.recordedSamples[i];
		if (val < 0) val = -val; /* ABS */
		if (val > max)
		{
			max = val;
		}
		average += val;
	}

	average = average / (double)numSamples;
	printf("sample max amplitude = %.8f\n", max);
	printf("sample average = %lf\n", average);

done:
	Pa_Terminate();
	if (data.recordedSamples)       /* Sure it is NULL or valid. */
		free(data.recordedSamples);
	if (err != paNoError)
	{
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;          /* Always return 0 or 1, but no other return codes. */
	}
	return err;
}

int						playback(void)
{
	PaStreamParameters  inputParameters, outputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;
	SAMPLE              max, val;
	double              average;

	std::cout << "PLAYBACK" << std::endl;

	data.maxIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; // Record for a few seconds.
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data.recordedSamples = (SAMPLE *)malloc(numBytes); // From now on, recordedSamples is initialised.
	data.run = true;
	data.writeIndex = 0;
	data.readIndex = 0;
	data.swap = false;
	data.maxIndex *= NUM_CHANNELS;
	if (data.recordedSamples == NULL)
	{
		printf("Could not allocate record array.\n");
		goto done;
	}
	for (i = 0; i<numSamples; i++) data.recordedSamples[i] = 0;

	err = Pa_Initialize();
	if (err != paNoError) goto done;

	// Playback recorded data.  --------------------------------------------
	data.writeIndex = 0;

	outputParameters.device = Pa_GetDefaultOutputDevice(); // default output device
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default output device.\n");
		goto done;
	}
	outputParameters.channelCount = 2;                     // stereo output
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	printf("\n=== Now playing back. ===\n"); fflush(stdout);
	err = Pa_OpenStream(
		&stream,
		NULL, // no input
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      // we won't output out of range samples so don't bother clipping them
		playCallback,
		&data);
	if (err != paNoError) goto done;

	if (stream)
	{
		err = Pa_StartStream(stream);
		if (err != paNoError) goto done;

		printf("Waiting for playback to finish.\n"); fflush(stdout);

		FILE	*fd;
		std::queue<std::pair<int, SAMPLE*>> stock;

		fd = fopen("recorded.raw", "r");
		if (fd != NULL)
		{
			stock = extractFromFile(fd);
			fclose(fd);
		}

		while ((err = Pa_IsStreamActive(stream)) == 1)
		{
			Pa_Sleep(1000);
			std::cout << "-";
			if (stock.size())
			{
				writeInList(&data, stock.front().second, stock.front().first);
				free(stock.front().second);
				stock.pop();
			}
			else
				data.run = !data.run;
		}
		if (err < 0) goto done;

		err = Pa_CloseStream(stream);
		if (err != paNoError) goto done;

		printf("Done.\n"); fflush(stdout);
		while (1);
	}

done:
	Pa_Terminate();
	if (data.recordedSamples)       // Sure it is NULL or valid.
		free(data.recordedSamples);
	if (err != paNoError)
	{
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1;          // Always return 0 or 1, but no other return codes.
	}
	return err;
}

int recordMe();
int playbackMe();

int main(void)
{
	recordMe();
	playbackMe();
}