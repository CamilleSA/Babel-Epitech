#include "ConnectionHandler.hpp"
#include <sqlite3.h>
#include <bitset>

#include "Queries.hpp"

using namespace babel::server::network;


connection_handler::connection_handler(io_service& io_service, network_manager* server) : sock_(io_service)
{
    io_service_ = &io_service;
    server_ = server;
}

connection_handler::instance connection_handler::create_instance(io_service& io_service, network_manager* server)
{
	return instance(new connection_handler(io_service, server));
}

tcp::socket& connection_handler::get_socket()
{
	return sock_;
}

io_service& connection_handler::get_io_service() const
{
    return *io_service_;
}

babel::server::server_user& connection_handler::getUser()
{
    return this->user_;
}


void connection_handler::start()
{
    read();
    std::cout << "New connection" << std::endl;
    send(std::string("200"));
}


void connection_handler::send(const std::string code)
{
    write_buffer_.clear();
    write_buffer_ = code + "\r\n";
    std::cout << "Sending : " + write_buffer_ << std::endl;
    async_write(sock_,
        buffer(write_buffer_),
        boost::bind(&connection_handler::write_handler, shared_from_this(),
            placeholders::error,
            placeholders::bytes_transferred));
}


void connection_handler::read()
{
    async_read_until(sock_,
        response_,
        "\0",
        boost::bind(&connection_handler::read_handler,
            shared_from_this(),
                    placeholders::error)
    );
}

void connection_handler::disconnect()
{
    sock_.close();
    server_->disconnect_client(this);
}

void connection_handler::read_handler(const boost::system::error_code& err)
{
    if (!err) {
        std::ostringstream ss;
        ss << &response_;
        const auto s = ss.str();
	    if (!s.empty() && s != "\r\n" && s != "\n")
	    {
		    const auto now = std::chrono::system_clock::now();
            std::time_t log_time = std::chrono::system_clock::to_time_t(now);
            std::cout << "[" << std::ctime(&log_time) << "] Received : " << s << std::endl;
            treat_request(s);
	    }
        ss.str("");
        ss.clear();
    }
    else {
        disconnect();
        return;
    }
    read();
}

void connection_handler::write_handler(const boost::system::error_code& err, size_t bytes_transferred)
{
    (void)bytes_transferred;
    if (!err)
        read();
}

std::vector<std::string> connection_handler::parse_request(const std::string request) const
{
    std::vector<std::string> parsed;
    std::stringstream ss(request);
    std::string token;
    while (std::getline(ss, token, ':')) {
        parsed.push_back(token);
    }
    return parsed;
}

void connection_handler::treat_request(std::string request)
{
    auto parsed_request = parse_request(request);
    for (auto query : queries)
    {
        if (query.code == std::stoi(parsed_request[0]))
		{
            parsed_request.erase(parsed_request.begin());
            return query.handler(server_->get_server(), *this, parsed_request);
		}
	}
    send(std::string("0"));
}
