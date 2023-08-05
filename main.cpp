#include "user_types.h"
#include "manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Destructor to delete linked list
UserManager::~UserManager() {
    // ...
}

void UserManager::readUsersFromFile(const string& filename, const string& userType) {
    ifstream file(filename);
    // Skip BOM
    file.ignore(3);
    string line, userId, username, password, name, statusStr;
    int age;
    bool status;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, userId, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        
        if (userType == "manager") {
            getline(ss, statusStr, ',');
            insertAtBeginning(userId, username, password, status);
        } else if (userType == "tenant") {
            getline(ss, name, ',');
            ss >> age; // Assuming age is the last value on the line
            insertAtBeginning(userId, username, password, false, name, age);
        } else {
            insertAtBeginning(userId, username, password);
        }
    }

    file.close();
}

bool UserManager::login(const string& username, const string& password) {
    User *temp = head;
    while (temp != nullptr) {
        if (temp->username == username && temp->password == password) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void UserManager::insertAtBeginning(const string& userId, const string& username, const string& password, bool status, const string& name, int age) {
    User *newUser;
    if (!name.empty()) {
        Tenant *tenant = new Tenant;
        tenant->name = name;
        tenant->age = age;
        newUser = tenant;
    } else if (status) {
        Manager *manager = new Manager;
        manager->status = status;
        newUser = manager;
    } else {
        newUser = new User;
    }

    newUser->userId = userId;
    newUser->username = username;
    newUser->password = password;
    newUser->next = head;
    head = newUser;
}

int main() {
    UserManager admins, managers, tenants;

    admins.readUsersFromFile("admin.csv", "admin");
    managers.readUsersFromFile("manager.csv", "manager");
    tenants.readUsersFromFile("tenant.csv", "tenant");

    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (admins.login(username, password)) {
        cout << "Logged in as Admin." << endl;
    } else if (managers.login(username, password)) {
        cout << "Logged in as Manager." << endl;
        managerMenu();
    } else if (tenants.login(username, password)) {
        cout << "Logged in as Tenant." << endl;
    } else {
        cout << "Login failed!" << endl;
    }

    return 0;
}
