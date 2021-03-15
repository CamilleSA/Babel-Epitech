
#include "DatabaseController.hpp"

#include <functional>
#include <iostream>
#include <sqlite3.h>

using namespace babel::server::database;



database_controller::database_controller(std::string path) : path_(path) {
}

//user database_controller::get_user(std::string username)
//{
//    //try {
//    //    auto all_users = get_db().get_all<user>();
//    //    for (auto &usr : all_users)
//    //    {
//	//        if (usr.username == username)
//	//        {
//	//	        return usr;
//	//        }
//    //    }
//    //    return {-1};
//    //}
//    //catch (std::system_error e) {
//    //    std::cout << e.what() << std::endl;
//    //}
//    //catch (...) {
//    //    std::cout << "unknown exeption" << std::endl;
//    //}
//}
//
//user database_controller::get_user(int id)
//{
//    //try {
//    //    auto to_find = get_db().get<user>(id);
//    //    std::cout << "user = " << to_find.username << " " << to_find.password << std::endl;
//    //    return to_find;
//    //}
//    //catch (std::system_error e) {
//    //    std::cout << e.what() << std::endl;
//    //}
//    //catch (...) {
//    //    std::cout << "unknown exeption" << std::endl;
//    //}
//}
//
//user database_controller::add_user(user new_user)
//{
//    //auto insertedId = get_db().insert(new_user);
//    //std::cout << "insertedId = " << insertedId << std::endl;
//    //new_user.id = insertedId;
//    //new_user.contact_key = insertedId;
//    //new_user.calljournal_key = insertedId;
//    //return new_user;
//}
