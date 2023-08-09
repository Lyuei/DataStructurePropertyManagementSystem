#pragma once

#include <string>

using namespace std;

class LinkedList;  // Forward declaration

// Base user class
class User
{
public:
    string userId;
    string username;
    string password;
    User(string userId, string username, string password);
    virtual void display() const;
};

// Derived admin class
class Admin : public User
{
public:
    Admin(string userId, string username, string password);
    void display() const override;
    void adminMenu(LinkedList &tenantList, LinkedList &managerList);
};

// Derived manager class
class Manager : public User
{
public:
    bool status;
    Manager(string userId, string username, string password, bool status);
    void display() const override;
    void managerMenu();    
    void displaySortedTenants(LinkedList& list);
    void searchTenantInfo(LinkedList& list);
    void setStatus(bool newStatus);
};

// Derived tenant class
class Tenant : public User
{
public:
    string name;
    int age;
    tm lastLogin;
    Tenant(string userId, string username, string password, string name, int age,tm lastLogin);
    void display() const override;
    void tenantMenu();
};
