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
    User(string userId, string username, string password);
    virtual ~User(); // Virtual destructor
    virtual void display() const;
};

// Derived admin class
class Admin : public User
{
public:
    Admin(string userId, string username, string password);
    void display() const override;
};

// Derived manager class
class Manager : public User
{
public:
    bool status;
    Manager(string userId, string username, string password, bool status);
    void display() const override;
};

// Derived tenant class
class Tenant : public User
{
public:
    string name;
    int age;
    Tenant(string userId, string username, string password, string name, int age);
    void display() const override;
};
