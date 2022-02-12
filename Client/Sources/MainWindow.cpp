#include "MainWindow.hpp"
#include "MainWindow.moc"
#include <string>

MyWindow::MyWindow() : QWidget()
{

	//QSound::play("../../Client/assets/SoundCo.mp3");

	//QMediaPlayer *player = new QMediaPlayer;
	//player->setMedia(QUrl::fromLocalFile("../../Client/assets/SoundCo.mp3"));
	
	QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage("../../Client/assets/Skype.png")));
    this->setPalette(palette);
	setWindowTitle(
		QApplication::translate("Babel client", "Babel client"));
	int window_width = QApplication::desktop()->width();
	int window_height = QApplication::desktop()->height();
	resize(window_width, window_height);
	QFontDatabase::addApplicationFont("../../Client/assets/Airfool.otf");


	Port = new QLabel(QApplication::translate("windowlayout", "Port:")); //creation des entree utilisateur host et port
	Port->setFont(QFont("Airfool", 35));
	Port->setStyleSheet("color: white");

	lineEditPort = new QLineEdit();
	lineEditPort->setFont(QFont("Airfool", 35));
	lineEditPort->setStyleSheet("color: #00b3f4;""border: 1px solid white;""border-radius:30%;");

	UserName = new QLabel(QApplication::translate("windowlayout", "Username:")); //creation des entree utilisateur host et port
	UserName->setFont(QFont("Airfool", 35));
	UserName->setStyleSheet("color: white");

	lineUserName = new QLineEdit();
	lineUserName->setFont(QFont("Airfool", 35));
	lineUserName->setStyleSheet("color: #00b3f4;""border: 1px solid white;""border-radius:30%;");

	Password = new QLabel(QApplication::translate("windowlayout", "Password:")); //creation des entree utilisateur host et port
	Password->setFont(QFont("Airfool", 35));
	Password->setStyleSheet("color: white");

	linePassword = new QLineEdit();
	linePassword->setFont(QFont("Airfool", 35));
	linePassword->setStyleSheet("color: #00b3f4;""border: 1px solid white;""border-radius:30%;");
	

	Host = new QLabel(QApplication::translate("windowlayout", "Host:"));
	Host->setFont(QFont("Airfool", 35));
	Host->setStyleSheet("color: white");


	lineEditHost = new QLineEdit();
	lineEditHost->setFont(QFont("Airfool", 35));
	lineEditHost->setStyleSheet("color: #00b3f4;""border: 1px solid white;""border-radius:30%;");

	QHBoxLayout *layout = new QHBoxLayout(); //layout
	layout->addWidget(Port);
	layout->addWidget(lineEditPort);
	layout->addWidget(UserName);
	layout->addWidget(lineUserName);
	layout->addWidget(Password);
	layout->addWidget(linePassword);
	layout->addWidget(Host);
	layout->addWidget(lineEditHost);

	UserName->setVisible(false);
	lineUserName->setVisible(false);
	Password->setVisible(false);
	linePassword->setVisible(false);
		
	setLayout(layout);
	

	boutonConnection = new QPushButton("Connect", this);

	boutonConnection->setGeometry(810, 700, 230, 100);
	boutonConnection->setFont(QFont("Airfool", 35));
	boutonConnection->setStyleSheet("background-color: white;""color: #00b3f4;" "border: 1px solid white;" "border-radius:30%;" );
	boutonConnection->setCursor(Qt::PointingHandCursor);

	boutonSignIn = new QPushButton("Sign In", this);
	boutonSignIn->setGeometry(810, 700, 230, 100);
	boutonSignIn->setFont(QFont("Airfool", 35));
	boutonSignIn->setStyleSheet("background-color: white;""color: #00b3f4;" "border: 1px solid white;" "border-radius:30%;" );
	boutonSignIn->setCursor(Qt::PointingHandCursor);

	boutonContacts = new QPushButton("Add Contact", this);
	boutonContacts->setGeometry(50, 500, 300, 100);
	boutonContacts->setFont(QFont("Airfool", 35));
	boutonContacts->setStyleSheet("background-color: white;""color:#00b3f4 ;" "border: 1px solid white;" "border-radius:30%;" );
	boutonContacts->setCursor(Qt::PointingHandCursor);

	
	boutonSignUp = new QPushButton("Sign Up", this);
	boutonSignUp->setGeometry(810, 700, 230, 100);
	boutonSignUp->setFont(QFont("Airfool", 35));
	boutonSignUp->setStyleSheet("background-color: white;""color: #00b3f4;" "border: 1px solid white;" "border-radius:30%;" );
	boutonSignUp->setCursor(Qt::PointingHandCursor);

	boutonCall = new QPushButton("", this);
	boutonCall->setGeometry(1000, 850, 230, 100);
	boutonCall->setFont(QFont("Airfool", 35));
	boutonCall->setStyleSheet("image: url(../../Client/assets/pngegg.png);" "border: 1px solid white;" "border-radius:30%;" );
	boutonCall->setCursor(Qt::PointingHandCursor);

	boutonSignIn->setVisible(false);
	boutonSignUp->setVisible(false);
	boutonContacts->setVisible(false);
	boutonCall->setVisible(false);

	connect(boutonConnection, SIGNAL(clicked()), this, SLOT(connectToServer()));
	//connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

void MyWindow::connectToServer()
{

	server_name = lineEditHost->text();
	server_port = lineEditPort->text().toUInt();
	_socket = new QTcpSocket(this);
	_socket->abort();
	_socket->connectToHost(server_name, server_port);

	boutonConnection->setVisible(false);
	Port->setVisible(false);
	Host->setVisible(false);
	lineEditPort->setVisible(false);
	lineEditHost->setVisible(false);

	lbl = new QLabel;
	movie = new QMovie("../../Client/assets/Loading.gif");
	lbl->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	lbl->setStyleSheet("border: solid 10px red;  background-color: rgba(255, 0, 0,127); color:rgb(0,255,0)");
	lbl->setGeometry(850, 800, 200, 200);
	lbl->setMovie(movie);
	lbl->show();
	movie->start();

	QMessageBox information;
	QFont font = QFont("Airfool", 35);
	information.setFont(font);
	information.addButton(tr("Ok"), QMessageBox::NoRole);
	information.setWindowFlags(Qt::FramelessWindowHint);
	information.setStyleSheet("color: #00b3f4;" "background-color: white;" "min-width: 650px;");
 	information.setText("Connecting to the server");
 	information.exec();

	if (_socket->waitForConnected()) {
		QMessageBox information_2;
		information_2.setFont(font);
		information_2.setText("Your connected !");
		information_2.addButton(tr("Ok"), QMessageBox::NoRole);
		information_2.setWindowFlags(Qt::FramelessWindowHint);
		information_2.setStyleSheet("color: #00b3f4;" "background-color: white;" "min-width: 450px;");
		information_2.exec();

		_socket->waitForReadyRead(3000);
		connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		/*const std::size_t count = datas.size();
		unsigned char* hex = new unsigned char[count];
		std::memcpy(hex, datas.constData(), count);*/
		//QString string(hex);
		qDebug() << datas;

		QMessageBox question;
		question.setFont(font);
		question.setText("Do you already have an account ?");
		
		question.setStyleSheet("color: #00b3f4;" "background-color: white;");

		QAbstractButton* pButtonNo = question.addButton(tr("No"), QMessageBox::NoRole);
		QAbstractButton* pButtonYes = question.addButton(tr("Yes"), QMessageBox::YesRole);
		question.setWindowFlags(Qt::FramelessWindowHint);
		question.exec();
		

		if (question.clickedButton() == pButtonYes) {
			lbl->setVisible(false);
			authentificationUsername();
			authentifiactionPassword();
			QObject::connect(boutonSignIn, SIGNAL(clicked()), this, SLOT(authentification()));


		} else if (question.clickedButton() == pButtonNo) {
			lbl->setVisible(false);
			registeration();
		}
	} else
		QMessageBox::warning(this, "Error", "Could not connect to the server");
	QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	//QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void MyWindow::authentification()
{
	//without
	username = lineUserName->text();
	password = linePassword->text();
	int login = 002;
	QByteArray authentification;
	authentification.prepend(login);
	authentification.prepend(":");
	authentification.append(username);
	authentification.append(":");
	authentification.append(password);
	authentification.append("\r\n");

	// Login to Server

	QMessageBox::warning(this, "Error", authentification);
	sendData(authentification);
	//_socket->waitForReadyRead(3000);
	//connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	QString stringData(datas);
	size_data += sizeof(stringData);
	stringData.remove(0, 16);
	QStringList pieces = stringData.split(":");
	if (int x = QString::compare(pieces.value(0), "1", Qt::CaseInsensitive) == 0)
		clean();
	else
		QMessageBox::warning(this, "Error", "login fail");

	connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void MyWindow::clean()
{
	boutonSignIn->setVisible(false);
	UserName->setVisible(false);
	Password->setVisible(false);
	Host->setVisible(false);
	lineUserName->setVisible(false);
	linePassword->setVisible(false);
}

void MyWindow::authentificationUsername()
{
	bool ok = false;
	boutonSignIn->setVisible(true);
	UserName->setVisible(true);
	lineUserName->setVisible(true);
}

void MyWindow::authentifiactionPassword()
{
	bool ok = false;

	boutonSignIn->setVisible(true);
	Password->setVisible(true);
	linePassword->setVisible(true);
}

std::string MyWindow::RandomString()
{
	std::string salt;
	static const char alphanum[] =
		"0123456789"
		"AZERTYUIOPQSDFGHJKLMWXCVBN"
		"azertyuiopqsdfghjklmwxcvbn";

	srand((unsigned)time(NULL) * _getpid());
	for (int i = 0; i < 12; i++)
		salt += alphanum[rand() % (sizeof(alphanum) - 1)];

	return salt;
}

void MyWindow::registeration()
{
	bool ok = false;

	QFont font = QFont("Airfool", 35);

	
	this->setStyleSheet("QInputDialog {background-color: #00b3f4;};");
	this->setFont(font);

	username = QInputDialog::getText(this, "Username", "What is your username", QLineEdit::Normal, QString(), &ok);

	int n = 4;
	QByteArray block;
	block.setNum(n);
	block.append(":");
	std::string salty = RandomString();
	QString salt = QString::fromStdString(salty);

	if (ok && !username.isEmpty())
	{
		block.append(username);
		block.append(":");
		password = QInputDialog::getText(this, "Password", "What is your password", QLineEdit::Normal, QString(), &ok);
		if (ok && !password.isEmpty()) {
			password = password + salt;
			block.append(password);
			block.append(":");
			block.append(salt);
		}
		else
			QMessageBox::critical(this, "Password", "ERROR you left the field empty");
	}
	else
		QMessageBox::critical(this, "Pseudo", "ERROR you left the field empty");
	block.append("\r\n");
	sendData(block);
	_socket->waitForReadyRead(3000);
	connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	datas.remove(0, 5);
	size_data += sizeof(datas);
	qDebug() << datas;
	//QStringList pieces = datas.split(":");
	this->setStyleSheet("QMessageBox {background-color: #00b3f4;};");

	if (int x = QString::compare(datas, "1\r\n", Qt::CaseInsensitive) == 0) {
		clean();
		QMessageBox::warning(this, "Register", "You are registred !");
		Call();
	}
	else
		QMessageBox::warning(this, "Error", "could not register");


	connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void MyWindow::Call()
{
		bool ok = false;

	QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage("../../Client/assets/unnamed.jpg")));
    this->setPalette(palette);

	boutonCall->setVisible(true);
	boutonContacts->setVisible(true);

	//this->setStyleSheet("QInput {background-color: #00b3f4;};");

	contact = QInputDialog::getText(this, "Add Contact", "What is it's name ?", QLineEdit::Normal, QString(), &ok);
	if (ok && !contact.isEmpty()) {
		// 1 - CLIENT A va envoyer une requete de co au Server
		my_port = _cliento.connectClient();

		// 2 - Client A envoie au Server une demande de connexion au Client B
		QByteArray blocki;
		int cally = 8;
		blocki.setNum(cally);
		blocki.append(":");
		blocki.append(contact);
		blocki.append(":");

		QByteArray _port;
		_port.setNum(my_port);

		blocki.append(_port);
		blocki.append("\r\n");
		sendData(blocki);
	}
	else
		QMessageBox::critical(this, "Port", "ERROR you left the field empty");

}

void MyWindow::AskForACall()
{
	//QByteArray block;
	//int cally = 006;
	//block.append(cally);
	//block.append(" ");
	//block.append(username); 
}

void MyWindow::sendData(QByteArray block)
{
	_socket->write(block);
	_socket->waitForBytesWritten(1000);
	_socket->waitForReadyRead(3000);
	connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void MyWindow::onReadyRead()
{
	datas = _socket->readAll();
	qDebug() << datas;
	//datas.remove(0, size_data);
	size_data += sizeof(datas);

	QList<QByteArray> pieces = datas.split(':');

	qDebug() << "DATA";
	qDebug() << datas;
	if (int x = QString::compare(pieces.value(0), "16", Qt::CaseInsensitive) == 0) {
		QMessageBox::warning(this, "appel", "you have an entering call");

		// 3 - Si Client B reçoit "16":Michel:IP:Port
		sender_username = pieces.value(1);
		sender_ip = pieces.value(2);
		std::string tmp_port(pieces.value(3).constData(), pieces.value(3).length());
		sender_port = std::stoi(tmp_port);

		// 4 - Client B bind son port
		my_port = _cliento.connectClient();

		// 5 - Client B envoie "64:Michel:port" au Server
		QByteArray block;
		int cally = 64;
		block.setNum(cally);
		block.append(":");
		block.append(sender_username);
		block.append(":");

		QByteArray _port;
		_port.setNum(my_port);

		block.append(_port);
		block.append("\r\n");
		qDebug() << "BLOCK";
		qDebug() << block;
		sendData(block);

		// 6 - Patrick parle avec Michel
		_cliento.talkClient(sender_port);
	}
	else if (int x = QString::compare(pieces.value(0), "64", Qt::CaseInsensitive) == 0) {
		// 7 - Michel récupère les infos de Patrick
		sender_ip = pieces.value(1);
		std::string tmp_port(pieces.value(2).constData(), pieces.value(2).length());
		int tmp_tmp_port = std::stoi(tmp_port);
		sender_port = tmp_tmp_port;

		// 8 - Michel parle avec Patrick
		_cliento.talkClient(sender_port);
	}
}

void MyWindow::disconnected()
{
	QMessageBox::critical(this, "Disconnect", "You were disconnected from the server");
}