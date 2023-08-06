#include "CSVReader.hpp"
#include <iostream>

using namespace std;

User *login(const string &username, const string &password, LinkedList& adminList, LinkedList& managerList, LinkedList& tenantList, Manager& manager) {
    User *user = adminList.login(username, password);
    if (user != NULL) {
        cout << "Welcome, admin " << user->username << "!\n";
        return user;
    }

    user = managerList.login(username, password);
    if (user != NULL) {
        cout << "Welcome, manager " << user->username << "!\n";
        manager.managerMenu();
        return user;
    }

    user = tenantList.login(username, password);
    if (user != NULL) {
        cout << "Welcome, tenant " << user->username << "!\n";
        return user;
    }

    cout << "Login failed!\n";
    return NULL;
}

int main() {
    Manager manager("userId", "username", "password", true);

    LinkedList adminList;
    readAdmins(adminList);
    adminList.display();

    LinkedList managerList;
    readManagers(managerList);
    managerList.display();

    LinkedList tenantList;
    readTenants(tenantList);
    tenantList.display();

    // Get username and password from user
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Try to login
    User* user = login(username, password, adminList, managerList, tenantList, manager);
}
