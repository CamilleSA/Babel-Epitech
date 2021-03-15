#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ConnexionUdp.hpp"
#include "Audio.hpp"

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <thread> 

class Client {
public:
	Client();

	void setupSound();
	int connectClient();
	void talkClient(int port);
	void closeSound();

	~Client();
private:
	AudioController _audio;
	ConnexionUdp _connect_client;

	bool in_call = false;
};

#endif