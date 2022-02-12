#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "ServerUser.hpp"

using namespace boost::asio;
using ip::tcp;


namespace babel
{
	namespace server
	{
		namespace network
		{
			/*
			 * fwd declaration to avoid cross dependencies
			 */
			class network_manager;


			/*
			 * class representing a client
			 */
			class connection_handler : public boost::enable_shared_from_this<connection_handler>
			{
			private:
				/// user associated with the client
				server_user user_;
				/// client's socket
				tcp::socket sock_;
				/// buffer used to read server's response
				streambuf response_;
				/// service instance to create the socket
				io_service* io_service_;
				/// server instance
				network_manager* server_;
				std::string write_buffer_;

			public:
				typedef boost::shared_ptr<connection_handler> instance;
				explicit connection_handler(io_service& io_service, network_manager *server);
				static instance create_instance(io_service& io_service, network_manager* server);
				tcp::socket& get_socket();
				io_service& get_io_service() const;
				connection_handler* get_handler() { return this; };
				void start();
				void send(const std::string message);
				void read();
				void read_handler(const boost::system::error_code& err);
				void write_handler(const boost::system::error_code& err, size_t bytes_transferred);
				std::vector<std::string> parse_request(std::string request) const;
				void treat_request(std::string request);
				void disconnect();
				server_user& getUser();
			};
		}
	}
}
