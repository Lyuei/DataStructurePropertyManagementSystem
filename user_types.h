#pragma once

#include <string>
#include <vector>

using namespace std;

struct User {
    string userId;
    string username;
    string password;

    User(const string& uid, const string& uname, const string& pwd);
    virtual bool validate(const string& uname, const string& pwd) const;
    virtual ~User() {}
};

struct Manager : public User {
    Manager(const string& uid, const string& uname, const string& pwd);
};

struct Tenant : public User {
    Tenant(const string& uid, const string& uname, const string& pwd);
};

vector<User*> readUsersFromFile(const string &filename);
bool login(const string &username, const string &password, const vector<User*>& users);
