#pragma once

#include <string>

namespace babel {
	namespace server {
		/*
		 * class representing a user connected to the server
		 */
		class server_user
		{
		private:
			/// the id of the user in the database, -1 if not logged in
			int user_id_ = -1;
			/// true if the user selected is online
			bool online_;
			/// user's client's IP address
			std::string remote_endpoint_ip_;
			/// user pseudonym, set to Anonymous if not logged in
			std::string username_ = "Anonymous";
			/// user's hashed password
			std::string validation_hash_ = "";
			/// user's salt
			std::string salt_ = "";
		public:
			/// class constructor
			server_user() : online_(true) {};
			/// class destructor
			~server_user() {};
			/// function called whenever a client is trying to register, creates a new object and
			/// adds a new entry in the database
			void create_new_user(int user_id, bool online, std::string remote_endpoint_ip,
			                     std::string username, std::string validation_hash, std::string salt);
			/// getters for each user's information stored
			int get_user_id() const { return user_id_; }
			std::string get_user_name() const { return username_; }
			std::string get_hash() const { return validation_hash_; }
			std::string get_salt() const { return salt_; }
			std::string get_user_ip() const { return remote_endpoint_ip_; }
			std::string to_string() const;
			bool get_user_status() const { return online_; }
		};

		inline void server_user::create_new_user(const int user_id, const bool online, const std::string remote_endpoint_ip,
		                                         const std::string username, const std::string validation_hash,
		                                         const std::string salt)
		{
			online_ = online;
			user_id_ = user_id;
			remote_endpoint_ip_ = remote_endpoint_ip;
			username_ = username;
			validation_hash_ = validation_hash;
			salt_ = salt;
		}

		inline std::string server_user::to_string() const
		{
			auto user = username_ + ":" + std::to_string(user_id_) + ":";
			if (online_)
			{
				user += "1";
			}
			else
			{
				user += "0";
			}
			return user;
		}
	}
}