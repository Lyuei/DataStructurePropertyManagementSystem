#include "User.hpp"

User::User(std::string userId, std::string username, std::string password)
    : userId(userId), username(username), password(password) {}

User::~User() {}

Admin::Admin(std::string userId, std::string username, std::string password)
    : User(userId, username, password) {}

Manager::Manager(std::string userId, std::string username, std::string password, bool status)
    : User(userId, username, password), status(status) {}

Tenant::Tenant(std::string userId, std::string username, std::string password, std::string name, int age)
    : User(userId, username, password), name(name), age(age) {}
