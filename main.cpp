#include "CSVReader.hpp"
#include <iostream>

using namespace std;

User *login(const string &username, const string &password, LinkedList &adminList, LinkedList &managerList, LinkedList &tenantList, Manager &manager, Tenant &tenant)
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
        tenant.tenantMenu();
        return user;
    }

    cout << "Access denied – the digital gates remain locked!\n";

    return NULL;
}

int main()
{
    Manager manager("userId", "username", "password", true);

    tm lastLogin = {0};
    lastLogin.tm_year = 100; // 2000
    lastLogin.tm_mon = 0;    // January
    lastLogin.tm_mday = 1;   // 1st day of the month

    Tenant tenant("userId", "username", "password", "Test Tenant", 30, lastLogin);

    LinkedList adminList;
    readAdmins(adminList);

    LinkedList managerList;
    readManagers(managerList);

    LinkedList tenantList;
    readTenants(tenantList);

    // Get username and password from user
    string username, password;
    do
    {
        cout << "Step right into the property management circus, where leaky faucets compose our symphony, elusive pests perform acrobatics, and tenant requests are our daily dose of comedy." << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Try to login
        User *user = login(username, password, adminList, managerList, tenantList, manager, tenant);
    }while (true);
}
