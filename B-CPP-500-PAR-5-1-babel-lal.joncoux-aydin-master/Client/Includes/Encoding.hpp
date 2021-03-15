#ifndef ENCODING_HPP
#define ENCODING_HPP

#define SAMPLE_RATE	(24000) 
#define FRAMES_PER_BUFFER (480) 
#define PA_SAMPLE_TYPE	paFloat32 

#include <opus.h>
#include <iostream>

class Encoding
{
	public:
		Encoding();

		void encodeAudio(const float* input, int* _len, unsigned char** audio_data);
		void decodeAudio(unsigned char* readaudiodata, float* pcm, int readlen);

		~Encoding();
	private:
		opus_int32	_frames_per_buf;
		OpusEncoder* _encoder;
		OpusDecoder* _decoder;

};

#endif