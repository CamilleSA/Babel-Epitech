#include <opus/opus.h>
#include <portaudio.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "MainWindow.hpp"
#include <iostream>
//#include "Client.hpp"
/**static void launch()
{
    Client new_client;
    new_client.connectClient();
}*/

static int launchGraphic(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MyWindow window;
    window.show();

    return (app.exec());
}

int main(int argc, char* argv[])
{
   // std::thread thread1(launch);

    launchGraphic(argc, argv);
    //thread1.join();
    return 0;
}