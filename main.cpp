#include "CSVReader.hpp"
#include <iostream>

using namespace std;

int main()
{
    LinkedList list;
    readAdmins(list);
    readManagers(list);
    readTenants(list);
    list.display();

    // Get username and password from user
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Try to login
    User *user = list.login(username, password);
    if (user == NULL)
    {
        cout << "Login failed!\n";
    }
    else
    {
        // Check the type of user and print a welcome message
        if (dynamic_cast<Admin *>(user) != NULL)
        {
            cout << "Welcome, admin " << user->username << "!\n";
        }
        else if (dynamic_cast<Manager *>(user) != NULL)
        {
            cout << "Welcome, manager " << user->username << "!\n";
        }
        else if (dynamic_cast<Tenant *>(user) != NULL)
        {
            cout << "Welcome, tenant " << user->username << "!\n";
        }
    }
}
