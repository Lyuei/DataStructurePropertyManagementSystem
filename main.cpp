#include "CSVReader.hpp"
#include <iostream>

using namespace std;

User *login(const string &username, const string &password, LinkedList &adminList, LinkedList &managerList, LinkedList &tenantList, Manager &manager)
{
    User *user = adminList.login(username, password);
    if (user != NULL)
    {
        cout << "Let the grand spectacle of control and regulation unfold! Welcome, " << user->username << "!\n";
        return user;
    }

    user = managerList.login(username, password);
    if (user != NULL)
    {
        cout << "It's showtime – time to orchestrate the daily madness! Welcome, " << user->username << "!\n";
        manager.managerMenu();
        return user;
    }

    user = tenantList.login(username, password);
    if (user != NULL)
    {
        cout << "Saddle up for the wild ride through the world of renting – where the walls have stories, and the carpet has seen things. Welcome, " << user->username << "!\n";
        return user;
    }

    cout << "Access denied – the digital gates remain locked!\n";

    return NULL;
}

int main()
{
    Manager manager("userId", "username", "password", true);

    LinkedList adminList;
    readAdmins(adminList);

    LinkedList managerList;
    readManagers(managerList);

    LinkedList tenantList;
    readTenants(tenantList);

    // Get username and password from user
    string username, password;
    cout << "Step right into the property management circus, where leaky faucets compose our symphony, elusive pests perform acrobatics, and tenant requests are our daily dose of comedy." << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "And now, let the spectacle begin as we unravel the mysteries of maintenance and unravel tenant tales.";

    // Try to login
    User *user = login(username, password, adminList, managerList, tenantList, manager);
}
