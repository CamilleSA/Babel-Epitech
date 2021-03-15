#ifndef CONNEXIONUDP_HPP
#define CONNEXIONUDP_HPP

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QSlider>
#include <QObject>
#include <QUdpSocket>

class ConnexionUdp : public QObject
{
	Q_OBJECT

	public slots:
		void onreadyRead();
	public:
		explicit ConnexionUdp(QObject* parent = 0);
		int startClient();
		void writeData(unsigned char* to_write, int port);
	private:
		QUdpSocket* udpSocket;
		int port;
};

#endif