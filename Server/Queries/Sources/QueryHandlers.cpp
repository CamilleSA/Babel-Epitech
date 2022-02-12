#include "QueryHandlers.hpp"
#include "Queries.hpp"

std::string generateUserId() {
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const auto max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(16, 0);
	std::generate_n(str.begin(), 16, randchar);
	return str;
}

const std::string serializeArgs(std::vector<std::string> args)
{
	std::ostringstream vts;
	if (!args.empty()) {
		std::copy(args.begin(), args.end() - 1,
			std::ostream_iterator<std::string>(vts,
				SEPARATOR));
		vts << args.back();
	}
	return vts.str();
}

void ping_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
                  [[maybe_unused]] std::vector<std::string> args)
{
	client.send("200");
}

void login_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
	std::vector<std::string> args)
{

	if (args.size() < 2) {
		client.send(serializeArgs({login_failure}));
		return;
	}
	if (client.getUser().get_user_id() != -1) {
		client.send(serializeArgs({ login_failure }));
		return;
	}
	//babel::server::database::user usr = server->db_controller_.get_user(args[0]);
	//if (usr.id == -1) {
	//	client.send(serializeArgs({ login_failure }));
	//}
	//else {
	//	std::cout << usr.username << "=" << usr.password << std::endl;
		client.send(serializeArgs({ login_success }));
	//}
}

void register_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
	std::vector<std::string> args)
{
	if (args.size() < 2) {
		client.send(serializeArgs({ register_failure }));
		return;
	}
	//babel::server::database::user usr = server->db_controller_.get_user(args[0]);
	//if (usr.id == -1) {
	//	client.send(register_already_exists);
	//}
	//else {
		client.send(serializeArgs({ register_success }));
		//auto created = server->db_controller_.add_user({ -1, args[0], args[1], args[2], -1, -1});
		client.getUser().create_new_user(server->get_user_list().size(), true, client.get_socket().remote_endpoint().address().to_string(),
			args[0], args[1], args[2]);
		server->get_user_list();
	//}
}

void call_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
	std::vector<std::string> args)
{
	if (client.getUser().get_user_id() == -1 || args.size() < 2) {
		client.send(call_failure);
		return;
	}
	auto to_call = server->get_client_by_username(args[0]);
	if (!to_call)
	{
		client.send(call_failure);
		return;
	} else
	{
		to_call->send("16:" + client.getUser().get_user_name() + ":" + client.getUser().get_user_ip() + ":" + args[1]);
	}
}

void logout_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
                    [[maybe_unused]] std::vector<std::string> args)
{
	if (client.getUser().get_user_id() == -1) {
		client.send(logout_failure);
		return;
	}
	client.getUser().create_new_user(-1, true, client.get_socket().remote_endpoint().address().to_string(),
		"Anonymous", "", "");
}

void quit_request(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
                  [[maybe_unused]] std::vector<std::string> args)
{
	client.disconnect();
}


void call_answered(babel::server::network::network_manager* server, babel::server::network::connection_handler& client,
	 std::vector<std::string> args)
{
	if (client.getUser().get_user_id() == -1 || args.size() < 2) {
		client.send(call_failure);
		return;
	}
	auto to_call = server->get_client_by_username(args[0]);
	if (!to_call)
	{
		client.send(call_failure);
		return;
	}
	else
	{
		to_call->send("64:" + client.getUser().get_user_ip() + ":" + args[1]);
	}
}