#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QInputDialog>
#include <QFontDatabase>
#include <QFormLayout>
#include <QtGui>
#include <QDialog>
#include <string>
#include <functional>
#include "Client.hpp"

#ifdef unix 
    #include <unistd.h>
#endif

class MyWindow : public QWidget // On h�rite de QWidget (IMPORTANT)
{
	Q_OBJECT

	public:
		MyWindow();

	public slots:
		void connectToServer();
		void onReadyRead();
		void disconnected();
		void authentification();

	private:
		void authentificationUsername();
		void createAccount();
		void registeration();
		//void SendAuthentificationPassword();
		void authentifiactionPassword();
		void sendData(QByteArray block);
		void clean();
		std::string RandomString();
		void AskForACall();
		void Call();

		//DATA
		int user_id;
		QString salt = "u6U62ZajFd";
		//std::string[] call_journal;
		//string[] contact;
		std::hash<char> hashed_password;
		QByteArray datas;
		char data;

		//UDP
		QString contact;
		Client _cliento;
		int my_port;
		int sender_port;
		QString sender_ip;
		QString sender_username;
		int size_data = 0;
		
		//QT GRAPHIC
		QPushButton *boutonConnection;
		QPushButton *boutonSignIn;
		QPushButton *boutonSignUp;
		QPushButton *boutonContacts;
		QPushButton *boutonCall;
		QTcpSocket  *_socket;
		QString server_name;
		quint16 server_port;
		QLabel *Port;
		QLabel *Host;
		QLabel *UserName;
		QLabel *Password;
		QLineEdit *lineUserName;
		QLineEdit *linePassword;
		QLineEdit *lineEditPort;
		QLineEdit *lineEditHost;
		QLineEdit *linePortCall;
		QString username;
		QString password;
		QDialog *dlg;
		QLabel *lbl;
		QMovie *movie;
		QInputDialog *inputDialog;

};

#endif // MAINWINDOW_H