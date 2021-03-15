#pragma once
#include <string>

#include "ServerNetworkManager.hpp"
#include "QueryHandlers.hpp"

/*
 * class to represent a query with its associated function and number of args
 */
class query
{
public:
	int code;
	void (*handler)(babel::server::network::network_manager *, babel::server::network::connection_handler&,
	                 std::vector<std::string>) = nullptr;
	size_t nb_arg = 0;
};

/*
 * List of all the queries available
 */
static std::vector<query> queries = {
	{42, ping_request, 0},
	{2, login_request, 2},
	{4, register_request, 3},
	{8, call_request, 1},
	{16, logout_request, 0},
	{32, quit_request, 0},
	{64, call_answered, 0},
};

//TODO refaire le protocole binaire (enum)
const std::string login_success = "1";
const std::string login_failure = "0";
const std::string register_success = "1";
const std::string register_failure = "0";
const std::string call_failure = "0";
const std::string logout_failure = "0";

#define SEPARATOR ":"