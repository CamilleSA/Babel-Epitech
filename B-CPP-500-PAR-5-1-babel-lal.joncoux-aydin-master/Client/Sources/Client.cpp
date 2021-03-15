#include "Client.hpp"

Client::Client() {
}

Client::~Client() {

}

void Client::setupSound() {
	_audio.launchAudio();
	_audio.initInput();
	_audio.initOutput();
	_audio.initStream();
	_audio.startStream();
}

void Client::closeSound() {
	std::cout << "Close sound" << std::endl;
	_audio.closeStream();
}

int Client::connectClient()
{
	// Setup Udp connection
	return _connect_client.startClient();
}

void Client::talkClient(int port)
{
	bool _iscalling = true;

	setupSound();
	std::cout << "stream is started" << std::endl;
	while (_iscalling) {
		_connect_client.onreadyRead();

		//	Envoie des paquets audios
		_connect_client.writeData(_audio.getAudioData(), port);
	}
	closeSound();
}