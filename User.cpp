#include "User.hpp"
#include "CSVReader.hpp"

User::User(string userId, string username, string password)
    : userId(userId), username(username), password(password) {}

User::~User() {}

void User::display() const
{
    cout << "User ID: " << userId << ", Username: " << username << "\n";
}

Admin::Admin(string userId, string username, string password)
    : User(userId, username, password) {}

void Admin::display() const
{
    cout << "Admin: "<< endl;
    User::display();
}

Manager::Manager(string userId, string username, string password, bool status)
    : User(userId, username, password), status(status) {}

void Manager::display() const
{
    cout << "Manager: "<< endl;
    User::display();
    cout << "Status: " << (status ? "Active" : "Inactive") << "\n";
}

void Manager::managerMenu()
{
    int choice;
    LinkedList tenantList;
    do
    {
        cout << "\nManager Menu: \n";
        cout << "1. Display all registered tenant details\n";
        cout << "2. Search tenant’s details\n";
        cout << "3. Delete tenant accounts based on inactivity status\n";
        cout << "4. Generate report on top 10 properties\n";
        cout << "5. Manage tenancy process upon renting request received\n";
        cout << "6. Manage payment of the confirmed tenancy\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            readTenants(tenantList);
            tenantList.display();
            break;
        case 2:
            // Call function to search tenant details
            break;
        case 3:
            // Call function to delete tenant accounts
            break;
        case 4:
            // Call function to generate report
            break;
        case 5:
            // Call function to manage tenancy process
            break;
        case 6:
            // Call function to manage payment
            break;
        case 7:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);
}

Tenant::Tenant(string userId, string username, string password, string name, int age, tm lastLogin)
    : User(userId, username, password), name(name), age(age), lastLogin(lastLogin) {}

void Tenant::display() const
{
    cout << "Tenant: "<< endl;
    User::display();
    cout << "Name: " << name
         << ", Age: " << age
         << ", Last Login: " << (lastLogin.tm_year + 1900) << "-" << (lastLogin.tm_mon + 1) << "-" << lastLogin.tm_mday << "\n";
}
