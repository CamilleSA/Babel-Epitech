#include "ServerNetworkManager.hpp"


using namespace babel::server::network;

void sql_stmt(const char* stmt, sqlite3* db)
{
    char* errmsg;
    int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
    if (ret != SQLITE_OK) {
        std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
}

network_manager::network_manager(io_service& io_service) : acceptor_(tcp::acceptor(io_service_, tcp::endpoint(tcp::v4(), 5060))), db_controller_("../../clients.db")
{
	try
	{
        start_accept();
	}
	catch (std::exception& e)
	{
        std::cerr << e.what() << std::endl;
        throw;
	}
}

network_manager::~network_manager()
{
    for (auto client : clients_)
    {
        if (client)
            delete client;
    }
}

network_manager* network_manager::get_server()
{
    return this;
}

void network_manager::start_accept()
{
	auto connection = connection_handler::create_instance(io_service_, this);

    // asynchronous accept operation and wait for a new connection.
    acceptor_.async_accept(connection->get_socket(),
        boost::bind(&network_manager::accept_handler, this, connection,
            placeholders::error));
}


void network_manager::accept_handler(connection_handler::instance connection, const boost::system::error_code& err)
{
    if (!err) {
        clients_.push_back(connection->get_handler());
        connection->start();
    }
    start_accept();
}

std::vector<std::string> network_manager::get_user_list()
{
    return {};
}

void network_manager::disconnect_client(connection_handler* client)
{
    clients_.erase(std::remove(clients_.begin(), clients_.end(), client), clients_.end());

}

void network_manager::run()
{
	while (true)
	{
        io_service_.run();
	}
}

babel::server::server_user& network_manager::get_user_by_id(int id_requested)
{
    for (auto client : clients_)
    {
        if (client) {
            if (client->getUser().get_user_id() == id_requested) {
                return client->getUser();
            }
        }
    }
}

babel::server::server_user& network_manager::get_user_by_username(std::string username)
{
    for (auto client : clients_)
    {
        if (client) {
            if (client->getUser().get_user_name() == username) {
                return client->getUser();
            }
        }
    }
    babel::server::server_user none;
    return none;
}

connection_handler *network_manager::get_client_by_username(std::string username)
{
    for (auto client : clients_)
    {
        if (client) {
            if (client->getUser().get_user_name() == username) {
                return client;
            }
        }
    }
    return nullptr;
}
