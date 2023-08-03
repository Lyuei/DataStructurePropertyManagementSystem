#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    string userId;
    string username;
    string password;

    User(const string& uid, const string& uname, const string& pwd)
        : userId(uid), username(uname), password(pwd) {}

    virtual bool validate(const string& uname, const string& pwd) const {
        return username == uname && password == pwd;
    }

    virtual ~User() {}
};

class Manager : public User {
    // Add manager-specific attributes and methods here if necessary.
public:
    Manager(const string& uid, const string& uname, const string& pwd)
        : User(uid, uname, pwd) {}
};

class Tenant : public User {
    // Add tenant-specific attributes and methods here if necessary.
public:
    Tenant(const string& uid, const string& uname, const string& pwd)
        : User(uid, uname, pwd) {}
};

vector<User*> readUsersFromFile(const string &filename) {
    ifstream file(filename);
    vector<User*> users;
    string line, userId, username, password;
    
        if (!file.is_open()) {  // Check if the file was successfully opened
        cerr << "Failed to open the file: " << filename << endl;
        exit(EXIT_FAILURE);  // Exit the program with an error code
    }

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        stringstream s(line);
        getline(s, userId, ',');
        getline(s, username, ',');
        getline(s, password, ',');

        if (filename == "C:\\Users\\leeyu\\Documents\\GitHub\\DataStructurePropertyManagementSystem\\") {
            users.push_back(new User(userId, username, password));
        } else if (filename == "C:\\Users\\leeyu\\Documents\\GitHub\\DataStructurePropertyManagementSystem\\manager.csv") {
            users.push_back(new Manager(userId, username, password));
        } else if (filename == "C:\\Users\\leeyu\\Documents\\GitHub\\DataStructurePropertyManagementSystem\\tenant.csv") {
            users.push_back(new Tenant(userId, username, password));
        }
    }

    return users;
}

bool login(const string &username, const string &password, const vector<User*>& users) {
    for (const auto& user : users) {
        if (user->validate(username, password)) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<User*> admins = readUsersFromFile("admin.csv");
    vector<User*> managers = readUsersFromFile("C:\\Users\\leeyu\\Documents\\GitHub\\DataStructurePropertyManagementSystem\\manager.csv");
    vector<User*> tenants = readUsersFromFile("C:\\Users\\leeyu\\Documents\\GitHub\\DataStructurePropertyManagementSystem\\tenant.csv");

    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (login(username, password, admins)) {
        cout << "Logged in as Admin." << endl;
    } else if (login(username, password, managers)) {
        cout << "Logged in as Manager." << endl;
    } else if (login(username, password, tenants)) {
        cout << "Logged in as Tenant." << endl;
    } else {
        cout << "Login failed!" << endl;
    }

    // Clean up dynamically allocated memory
    for (auto& user : admins) delete user;
    for (auto& user : managers) delete user;
    for (auto& user : tenants) delete user;

    return 0;
}
