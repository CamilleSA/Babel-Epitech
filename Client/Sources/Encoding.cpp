#include "Encoding.hpp"

Encoding::Encoding() {
	int error;

	_frames_per_buf = FRAMES_PER_BUFFER;
	_encoder = opus_encoder_create(SAMPLE_RATE, 2, OPUS_APPLICATION_VOIP, &error);
	_decoder = opus_decoder_create(SAMPLE_RATE, 2, &error);
	opus_encoder_ctl(_encoder, OPUS_GET_BANDWIDTH(&_frames_per_buf));
}

Encoding::~Encoding() {
	//opus_encoder_destroy(_encoder);
//	opus_decoder_destroy(_decoder);
}

void Encoding::encodeAudio(const float* input, int* _len, unsigned char** audio_data)
{
	*audio_data = (unsigned char*)malloc(sizeof(char) * _frames_per_buf);
	// Verify malloc

	*_len = opus_encode_float(_encoder, input, FRAMES_PER_BUFFER, *audio_data, _frames_per_buf);
}

void Encoding::decodeAudio(unsigned char* readaudiodata, float* pcm, int readlen)
{
	if (opus_decode_float(_decoder, readaudiodata, readlen, pcm, FRAMES_PER_BUFFER, 0) < 0) {
		std::cout << "Error : Decoding" << std::endl;
	}
}