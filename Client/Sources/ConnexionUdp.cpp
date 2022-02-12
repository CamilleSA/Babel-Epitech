#include "ConnexionUdp.hpp"

ConnexionUdp::ConnexionUdp(QObject* parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

int ConnexionUdp::startClient()
{
    // Create port 
    port = (rand() % (4000 - 1030 + 1)) + 1030;
    udpSocket->bind(QHostAddress::LocalHost, port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onreadyRead()));
    return port;
}

void ConnexionUdp::writeData(unsigned char* to_write, int port)
{
    QByteArray Data(reinterpret_cast<const char*>(&to_write[0]), std::extent<decltype(to_write)>::value);

    udpSocket->writeDatagram(Data, QHostAddress::LocalHost, port);
}

void ConnexionUdp::onreadyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(udpSocket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort = 0;

   // while (udpSocket->hasPendingDatagrams()) {
    udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
   // }
    std::string stdString(buffer.constData(), buffer.length());
    if (!stdString.empty()) {
        qDebug() << "Message from: " << sender.toString();
        qDebug() << "Message port: " << senderPort;
        
    }
}