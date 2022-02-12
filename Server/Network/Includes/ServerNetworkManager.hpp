#pragma once

#include <string>
#include <boost/asio.hpp>

#include "ConnectionHandler.hpp"
#include "ServerUser.hpp"
#include "DatabaseController.hpp"

using ip::tcp;

namespace babel
{
	namespace server
	{
		namespace network
		{
			/*
			 * class whose main job is to handle incoming connections
			 */
			class network_manager : public std::enable_shared_from_this<network_manager>
			{
			private:
				///service to manage the inputs and outputs of each connection
				io_service io_service_;
				/// used for accepting new socket connections.
				tcp::acceptor acceptor_;
				///the list of the connected clients
				std::vector<connection_handler*> clients_;
				///function called whenever a new client is connected to the server
				void start_accept();
			public:
				database::database_controller db_controller_;
				/// class constructor
				explicit network_manager(io_service& io_service);
				/// class destructor
				~network_manager();
				/// getter to be able to use an instance of the server (in order to retrieve clients for example)
				network_manager* get_server();
				/// function used to return the list of all the clients
				std::vector<std::string> get_user_list();
				/// function used to disconnect the client, close the socket and delete it from the list
				void disconnect_client(connection_handler *client);
				/// function called whenever a new client is trying to connect to the server, calling start_accept afterwards
				void accept_handler(connection_handler::instance connection, const boost::system::error_code& err);
				/// makes the io_service available while the server is up
				void run();
				/// gets the user with the corresponding ID
				server_user& get_user_by_id(int id_requested);
				server_user& get_user_by_username(std::string username);
				connection_handler *get_client_by_username(std::string username);
			};
		}
	}
}
