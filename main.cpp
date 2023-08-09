#include "CSVReader.hpp"
#include <iostream>

using namespace std;

User *login(const string &username, const string &password, LinkedList &adminList, LinkedList &managerList, LinkedList &tenantList, Admin &admin, Manager &manager, Tenant &tenant)
{
    User *user = adminList.login(username, password);
    if (user != NULL)
    {
        cout << "Let the grand spectacle of control and regulation unfold! Welcome, \n" << user->username << "!\n";
        admin.adminMenu(tenantList, managerList);
        return user;
    }

    user = managerList.login(username, password);
    if (user != NULL)
    {
        cout << "It's showtime – time to orchestrate the daily madness! Welcome, \n" << user->username << "!\n";
        manager.managerMenu();
        return user;
    }

    user = tenantList.login(username, password);
    if (user != NULL)
    {
        cout << "Saddle up for the wild ride through the world of renting – where the walls have stories, and the carpet has seen things. Welcome, \n" << user->username << "!\n";
        tenant.tenantMenu();
        return user;
    }

    cout << "Access denied – the digital gates remain locked!\n";

    return NULL;
}

int main()
{
    // Initialise User Object
    Admin admin("userId", "username", "password");
    Manager manager("userId", "username", "password", true);
    Tenant tenant("userId", "username", "password", "Test Tenant", 30, {0, 0, 0, 1, 0, 100});

    LinkedList adminList;
    Admin *newAdmin = new Admin("1", "admin", "admin");
    adminList.insert(newAdmin);

    LinkedList managerList;
    Manager *newManager = new Manager("11", "manager", "manager", 1);
    Manager *newManager1 = new Manager("12", "manager1", "manager1", 0);
    managerList.insert(newManager);
    managerList.insert(newManager1);

    LinkedList tenantList;
    Tenant *newTenant = new Tenant("11", "tenant", "tenant", "yuwei", 21, {0, 0, 0, 1, 0, 100});
    tenantList.insert(newTenant);

    // Get username and password from user
    string username, password;
    do
    {
        cout << "\nStep right into the property management circus, where leaky faucets compose our symphony, elusive pests perform acrobatics, and tenant requests are our daily dose of comedy." << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Try to login
        User *user = login(username, password, adminList, managerList, tenantList, admin, manager, tenant);
    } while (true);
}
