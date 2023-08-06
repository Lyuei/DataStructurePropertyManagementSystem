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
    cout << "Admin: " << endl;
    User::display();
}

Manager::Manager(string userId, string username, string password, bool status)
    : User(userId, username, password), status(status) {}

void Manager::display() const
{
    cout << "Manager: " << endl;
    User::display();
    cout << "Status: " << (status ? "Active" : "Inactive") << "\n";
}

void Manager::managerMenu()
{
    int choice;
    string userIdToDelete;
    LinkedList tenantList;
    readTenants(tenantList);
    do
    {
        cout << "\nManager's Realm: \n";
        cout << "1. Unveil the Details of Registered Tenants\n";
        cout << "2. Embark on a Quest for Tenant Info\n";
        cout << "3. Banish Inactive Tenants into the Abyss\n";
        cout << "4. Summon the Legends of Top 10 Properties\n";
        cout << "5. Dive into the Dance of Tenancy Process\n";
        cout << "6. Tame the Wild Beast of Confirmed Payments\n";
        cout << "7. Logout\n";
        cout << "Enter Your Command: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            tenantList.display();
            break;
        case 2:

            // Call function to search tenant details
            break;
        case 3:
            cout << "Enter the sacrificial User ID of the tenant you wish to obliterate, or 'cancel' to backtrack: ";
            cin >> userIdToDelete;
            if (userIdToDelete == "cancel")
            {
                cout << "Deletion ritual aborted – their digital existence lives on.\n";
            }
            else
            {
                // Let the darkness consume the tenant, wiping them from the list and the scrolls
                tenantList.remove(userIdToDelete);
                deleteTenantFromFile("csv_files/tenant.csv", userIdToDelete);
                cout << "Tenant bearing User ID " << userIdToDelete << " has been vanquished from our realms.\n";
            }

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
            cout << "Commencing the art of logout...\n";
            break;
        default:
            cout << "Ah, the land of indecision! Enter a realm between 1 and 7, mortal.\n";
        }
    } while (choice != 7);
}

Tenant::Tenant(string userId, string username, string password, string name, int age, tm lastLogin)
    : User(userId, username, password), name(name), age(age), lastLogin(lastLogin) {}

void Tenant::display() const
{
    cout << "Tenant: " << endl;
    User::display();
    cout << "Name: " << name
         << ", Age: " << age
         << ", Last Login: " << (lastLogin.tm_year + 1900) << "-" << (lastLogin.tm_mon + 1) << "-" << lastLogin.tm_mday << "\n";
}
