//
// Made by marco
//

#ifndef AUDIO_HPP_
# define AUDIO_HPP_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include "portaudio.h"

#define SAMPLE_RATE			(44100)
#define FRAMES_PER_BUFFER	(512)
#define NUM_SECONDS			(2)
#define NUM_CHANNELS		(2)
#define DITHER_FLAG			(0)

namespace babel
{
	class Audio
	{
	private:
		PaStream	*_stream;
		PaError		_err;

	private:
		float*		_recordedData;
		int			_sizeRecordedData;

	private:
		float*		_toPlayData;
		int			_sizeToPlayData;

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
		int			run(void);
		int			stopStream(void);

	public:
		float		*getRecord(void) const;
		int			getRecordSize(void) const;
		int			getPlayBackSize(void) const;

	public:
		void		setPlayBack(float *playMe, int size);

	public:
		void		cleanRecord(void);
	};
}

#endif