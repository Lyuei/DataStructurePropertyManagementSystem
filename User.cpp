#include "LinkedList.hpp"
#include "CSVReader.hpp"
#include <chrono>
#include <algorithm>
#include <vector>

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

void Manager::displaySortedTenants(LinkedList &tenantList)
{
    // Get the current date
    auto now = chrono::system_clock::now();
    time_t now_time_t = chrono::system_clock::to_time_t(now);

    // Convert the tenant list to a vector
    vector<Tenant *> tenants = tenantList.to_vector();
    vector<User *> users(tenants.begin(), tenants.end());

    // Sort the vector by last login date
    sort(users.begin(), users.end(), [](User *a, User *b)
         {
        Tenant* tenantA = dynamic_cast<Tenant*>(a);
        Tenant* tenantB = dynamic_cast<Tenant*>(b);
        if (tenantA != nullptr && tenantB != nullptr) {
            return difftime(mktime(&(tenantA->lastLogin)), mktime(&(tenantB->lastLogin))) < 0;
        }
        return false; });

    // Display the sorted tenants
    for (User *user : users)
    {
        Tenant *tenant = dynamic_cast<Tenant *>(user);
        if (tenant != nullptr)
        {
            tenant->display();

            // Calculate and display the number of days since the last login
            time_t lastLogin_time_t = mktime(&tenant->lastLogin);
            chrono::system_clock::time_point now_time_point = chrono::system_clock::from_time_t(now_time_t);
            chrono::system_clock::time_point lastLogin_time_point = chrono::system_clock::from_time_t(lastLogin_time_t);
            chrono::duration<int, std::ratio<60 * 60 * 24>> days_since_last_login = chrono::duration_cast<chrono::duration<int, std::ratio<60 * 60 * 24>>>(now_time_point - lastLogin_time_point);
            cout << "Days since last login: " << days_since_last_login.count() << "\n";
        }
    }
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
            // Iterate over the list of tenants
            displaySortedTenants(tenantList);
            cout << "Enter the sacrificial User ID of the tenant you wish to obliterate, or 'cancel' to backtrack: ";
            cin >> userIdToDelete;
            if (userIdToDelete == "cancel")
            {
                cout << "Deletion ritual aborted – their digital existence lives on.\n";
            }
            else
            {
                // Delete tenant from linked list and csv file
                tenantList.remove(userIdToDelete);
                deleteTenantFromFile("csv_files/tenant.csv", userIdToDelete);
                cout << "Tenant bearing User ID " << userIdToDelete << " has been vanquished from our realms.\n";
            }
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

// void Tenant::tenantMenu()
// {
//     int choice;
//     string propertyId;
//     LinkedList propertyList;
//     // Assuming readProperties is a function that reads property data into propertyList
//     // readProperties(propertyList);

//     do
//     {
//         cout << "\nTenant's Realm: \n";
//         cout << "1. Explore the Property Collection\n";
//         cout << "2. Sort Properties\n";
//         cout << "3. Embark on the Property Hunt\n";
//         cout << "4. Show Love to a Property (Save as Favorite)\n";
//         cout << "5. Initiate Rent Request\n";
//         cout << "6. Witness Renting Chronicles\n";
//         cout << "7. Logout\n";
//         cout << "Enter Your Command: ";

//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             // propertyList.display();
//             break;
//         case 2:
//             // Call function to sort properties
//             break;
//         case 3:
//             // Call function to search property
//             break;
//         case 4:
//             // Call function to save favorite property
//             break;
//         case 5:
//             // Call function to place rent request
//             break;
//         case 6:
//             // Call function to display renting history
//             break;
//         case 7:
//             cout << "Logging out...\n";
//             break;
//         default:
//             cout << "Ah, the land of indecision! Enter a realm between 1 and 7, mortal.\n";
//         }
//     } while (choice != 7);
// }

