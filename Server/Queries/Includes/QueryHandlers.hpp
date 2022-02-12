#pragma once
#include <string>
#include <vector>
#include "ServerNetworkManager.hpp"
#include "ConnectionHandler.hpp"

/// All the requests available
/// Ping : sends a pong to the sender
/// Login : search for corresponding user and retrieve user's information if found
/// Register : Adds a new user in the database
/// Call : make the connection between the caller and the called client
/// Logout : logout the client
/// Quit : disconnect the client and closes the socket
void ping_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void login_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void register_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void call_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void logout_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void quit_request(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
void call_answered(babel::server::network::network_manager*, babel::server::network::connection_handler&,
	std::vector<std::string>);
