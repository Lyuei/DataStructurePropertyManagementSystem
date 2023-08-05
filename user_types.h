#pragma once

#include <string>
#include <vector>

using namespace std;

struct User {
    string userId;
    string username;
    string password;
    User *next;

    User() : next(nullptr) {}
    virtual ~User() {} // Virtual destructor
};

struct Manager : public User {
    bool status;

    Manager() : status(false) {}
};

struct Tenant : public User {
    string name;
    int age;

    Tenant() : name(""), age(0) {}
};

class UserManager {
private:
    User *head;

public:
    UserManager() : head(nullptr) {}
    ~UserManager(); // Destructor to delete linked list
    void readUsersFromFile(const string& filename, const string& userType);
    bool login(const string& username, const string& password);
    void insertAtBeginning(const string& userId, const string& username, const string& password, bool status = false, const string& name = "", int age = 0);
};
