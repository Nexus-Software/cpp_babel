//
// Made by marco
//

#ifndef AUDIO_HPP_
# define AUDIO_HPP_

#include <iostream>
#include <vector>
#include "portaudio.h"

#define SAMPLE_RATE			(48000)
#define FRAMES_PER_BUFFER	(480)
#define NUM_SECONDS			(1)
#define LATENCY_CONSTANT	(10)
#define NUM_CHANNELS		(2)
#define FRAME_SIZE			(960)
#define MAX_PACKET			(FRAME_SIZE * NUM_CHANNELS * 2)
#define MAX_FRAME_SIZE		(960 * 6)

typedef std::vector<float> B_SAMPLE;

namespace babel
{
	class Audio
	{
	private:
		PaStream	*_stream;
		PaError		_err;

	private:
		B_SAMPLE	_recordedData;

	private:
		bool		_record;
		bool		_difuse;

	public:
		explicit	Audio(void);
		virtual		~Audio(void);

	public:
		int			initialize(void);
		int			terminate(void);

	public:
		int			startStream(bool record = true, bool difuse = true);
		int			stopStream(void);
		bool 		play(B_SAMPLE);
		B_SAMPLE	record(void);

	public:
		void		cleanRecord(void);
	};
}

#endif