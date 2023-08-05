#include "User.hpp"

User::User(std::string userId, std::string username, std::string password)
    : userId(userId), username(username), password(password) {}

User::~User() {}

void User::display() const
{
    cout << "User ID: " << userId << ", Username: " << username << "\n";
}

Admin::Admin(std::string userId, std::string username, std::string password)
    : User(userId, username, password) {}

void Admin::display() const
{
    cout << "Admin: ";
    User::display();
}

Manager::Manager(std::string userId, std::string username, std::string password, bool status)
    : User(userId, username, password), status(status) {}

void Manager::display() const
{
    cout << "Manager: ";
    User::display();
    cout << "Status: " << (status ? "Active" : "Inactive") << "\n";
}

Tenant::Tenant(std::string userId, std::string username, std::string password, std::string name, int age)
    : User(userId, username, password), name(name), age(age) {}

void Tenant::display() const
{
    cout << "Tenant: ";
    User::display();
    cout << "Name: " << name << ", Age: " << age << "\n";
}
