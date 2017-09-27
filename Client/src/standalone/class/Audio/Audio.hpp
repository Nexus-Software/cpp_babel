//
// Made by marco
//

#ifndef AUDIO_HPP_
# define AUDIO_HPP_

#include <iostream>
#include <array>
#include "portaudio.h"

#define SAMPLE_RATE			(44100)
#define FRAMES_PER_BUFFER	(512)
#define NUM_SECONDS			(1)
#define LATENCY_CONSTANT	(10)
#define NUM_CHANNELS		(2)

#define RECORD_SIZE			(SAMPLE_RATE * NUM_CHANNELS)

typedef std::array<float, RECORD_SIZE> B_SAMPLE;

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
		bool 		play(B_SAMPLE, int);
		B_SAMPLE	record(void);

	public:
		B_SAMPLE	getRecord(void) const;
		int			getRecordSize(void) const;

	public:
		void		cleanRecord(void);
	};
}

#endif