#include <iostream>
#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "ServerNetworkManager.hpp"

int main(int argc, char** argv)
{
    try
    {
        io_service io_service;
        babel::server::network::network_manager server(io_service);
        server.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
