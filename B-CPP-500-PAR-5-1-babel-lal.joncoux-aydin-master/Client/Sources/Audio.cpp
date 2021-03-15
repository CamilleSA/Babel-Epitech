#include "Audio.hpp"

AudioController::AudioController() {
    _instream = NULL;
    _outstream = NULL;
}

AudioController::~AudioController() {
    if (_instream)
        Pa_CloseStream(_instream);
    if (_outstream)
        Pa_CloseStream(_outstream);
    Pa_Terminate();
}

int AudioController::launchAudio()
{
    _error = Pa_Initialize();
    if (_error != paNoError) {
        std::cout << "Error : Initialize Audio" << std::endl;
        return 84;
    }
    return 0;
}

void AudioController::initInput() {
    _inparam.device = Pa_GetDefaultInputDevice();
    _inparam.channelCount = 2;
    _inparam.sampleFormat = paFloat32;
    _inparam.suggestedLatency = Pa_GetDeviceInfo(_inparam.device)->defaultLowInputLatency;
    _inparam.hostApiSpecificStreamInfo = NULL;
}

void AudioController::initOutput() {
    _outparam.device = Pa_GetDefaultOutputDevice();
    _outparam.channelCount = 2;
    _outparam.sampleFormat = paFloat32;
    _outparam.suggestedLatency = Pa_GetDeviceInfo(_outparam.device)->defaultLowOutputLatency;
    _outparam.hostApiSpecificStreamInfo = NULL;
}

int AudioController::initStream() {
    _error = Pa_OpenStream(&_instream, &_inparam, NULL, 24000, 480, paClipOff, recordCallback, this);
    if (_error != paNoError) {
        std::cout << "Error : Opening Audio Stream" << std::endl;
        return 84;
    }
    _error = Pa_OpenStream(&_outstream, NULL, &_outparam, 24000, 480, paClipOff, playCallback, this);
    if (_error != paNoError)
    {
        std::cout << "Error : Opening Audio Stream" << std::endl;
        return 84;
    }
    return 0;
}

int AudioController::startStream() {
    _error = Pa_StartStream(_instream);
    if (_error != paNoError)
    {
        std::cout << "Error : Start Audio Stream" << std::endl;
        return 84;
    }
    _error = Pa_StartStream(_outstream);
    if (_error != paNoError)
    {
        std::cout << "Error : Start Audio Stream" << std::endl;
        return 84;
    }
    return 0;
}

int AudioController::closeStream() {
    if (_instream)
    {
        _error = Pa_StopStream(_instream);
        if (_error != paNoError)
        {
            std::cout << "Error : Stop Audio Stream" << std::endl;
            return 84;
        }
    }
    if (_outstream)
    {
        _error = Pa_StopStream(_outstream);
        if (_error != paNoError)
        {
            std::cout << "Error : Stop Audio Stream" << std::endl;
            return 84;
        }
    }
    return 0;
}

int recordCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    AudioController* _record = (AudioController*)userData;
    const float* input = (const float*)inputBuffer;
    unsigned char* audio_data = NULL;
    int _len = 0;

    // NO WARNING
    (void)timeInfo;
    (void)statusFlags;
    (void)outputBuffer;

    _record->getEncoding().encodeAudio(input, &_len, &audio_data);
    _record->setAudioData(audio_data);
    _record->setLen(_len);
    return paContinue;
}

int playCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    AudioController* _play = (AudioController*)userData;
    float* out = (float*)outputBuffer;

    // NO WARNING
    (void)timeInfo;
    (void)statusFlags;
    (void)inputBuffer;

    _play->getEncoding().decodeAudio(_play->getAudioData(), out, _play->getLen());
    return paContinue;
}