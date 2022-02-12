#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>

namespace babel
{
	namespace server
	{
		namespace database
		{
			struct user {
				int id;
				std::string username;
				std::string password;
				std::string salt;
				int contact_key;
				int calljournal_key;
			};

			struct contact {
				int id;
				std::string username;
				int status;
				int users_key;
			};

			struct call_journal {
				int id;
				std::string username;
				int call_status;
				int users_key;
			};

			using namespace sqlite_orm;
			
			class database_controller
			{
			private:
				std::string path_;
			public:
				explicit database_controller(std::string path);
				//user get_user(std::string username);
				//user get_user(int id);
				//user add_user(user new_user);
				~database_controller() {}
			};
		}
	}
}
