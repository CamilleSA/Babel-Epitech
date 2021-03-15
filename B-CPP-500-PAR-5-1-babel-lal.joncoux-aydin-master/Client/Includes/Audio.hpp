#ifndef AUDIO_HPP
#define AUDIO_HPP

// TODO : encapulsate
#include "portaudio.h"
#include "Encoding.hpp"
#include <iostream>

class AudioController {
public:
    AudioController();

    // INIT
    int launchAudio();
    void initInput();
    void initOutput();

    // MANAGE STREAM
    int initStream();
    int startStream();
    int closeStream();

    // GETTERS
    Encoding getEncoding() {
        return _opusService;
    }
    unsigned char* getAudioData() {
        return _audiodata;
    }
    int getLen() {
        return _len;
    }
    unsigned char* getReadAudioData() {
        return _readaudiodata;
    }
    int getReadLen() {
        return _readlen;
    }

    // SETTERS
    void setAudioData(unsigned char* audio_data) {
        _audiodata = audio_data;
    }

    void setLen(int len) {
        _len = len;
    }
    void setReadAudioData(unsigned char* audio_data) {
        _readaudiodata = audio_data;
    }

    void setReadLen(int len) {
        _readlen = len;
    }

    ~AudioController();
private:
    PaStream* _instream;
    PaStream* _outstream;
    PaError _error;
    PaStreamParameters _inparam;
    PaStreamParameters _outparam;
    Encoding _opusService;
    int _len = 0;
    int _readlen = 0;
    unsigned char* _audiodata;
    unsigned char* _readaudiodata;
};

int recordCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);
int playCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

#endif