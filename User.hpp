#pragma once

#include <string>
#include <iostream>

using namespace std;

// Base user class
class User
{
public:
    string userId;
    string username;
    string password;
    User(string userId, string username, string password)
        : userId(userId), username(username), password(password) {}
    virtual ~User() {} // Virtual destructor
    virtual void display() const
    {
        cout << "User ID: " << userId << ", Username: " << username << "\n";
    }
};

// Derived admin class
class Admin : public User
{
public:
    Admin(string userId, string username, string password)
        : User(userId, username, password) {}
    void display() const override
    {
        cout << "Admin: ";
        User::display();
    }
};

// Derived manager class
class Manager : public User
{
public:
    bool status;
    Manager(string userId, string username, string password, bool status)
        : User(userId, username, password), status(status) {}
    void display() const override
    {
        cout << "Manager: ";
        User::display();
        cout << "Status: " << (status ? "Active" : "Inactive") << "\n";
    }
};

// Derived tenant class
class Tenant : public User
{
public:
    string name;
    int age;
    Tenant(string userId, string username, string password, string name, int age)
        : User(userId, username, password), name(name), age(age) {}
    void display() const override
    {
        cout << "Tenant: ";
        User::display();
        cout << "Name: " << name << ", Age: " << age << "\n";
    }
};
