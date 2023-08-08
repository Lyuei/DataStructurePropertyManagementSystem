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
        
        // Format last login date as dd-mm-yyyy
        char lastLoginDate[11];
        strftime(lastLoginDate, sizeof(lastLoginDate), "%d-%m-%Y", &tenant->lastLogin);
        
        cout << "Last login: " << lastLoginDate << ", Days since last login: " << days_since_last_login.count() << "\n";
    }
}

}

void Manager::managerMenu()
{
    string choice;
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

        if (choice == "1")
        {
            tenantList.display();
        }
        else if (choice == "2")
        {
            searchTenantInfo(tenantList);
        }
        else if (choice == "3")
        {
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
        }
        else if (choice == "4")
        {
            // Call function to generate report
        }
        else if (choice == "5")
        {
            // Call function to manage tenancy process
        }
        else if (choice == "6")
        {
            // Call function to manage payment
        }
        else if (choice == "7")
        {
            cout << "Commencing the art of logout...\n";
        }
        else
        {
            cout << "Ah, the land of indecision! Enter a realm between 1 and 7, mortal.\n";
        }
    } while (choice != "7");
}

void Manager::searchTenantInfo(LinkedList& list)
{
    int criteriaChoice;
    cout << "\nChoose a criteria to search by: \n";
    cout << "1. User ID\n";
    cout << "2. Name\n";
    cout << "3. Age\n";
    cout << "4. Last Login\n";
    cout << "Enter Your Command: ";
    cin >> criteriaChoice;

    switch (criteriaChoice)
    {
    case 1:
    {
        string userId;
        cout << "Enter User ID to search: ";
        cin >> userId;
        list.searchTenantByUserId(userId);
        break;
    }
    case 2:
    {
        string name;
        cout << "Enter Name to search: ";
        cin.ignore();       // Ignore the newline character in the input buffer
        getline(cin, name); // Use getline to read a full line of text
        list.searchTenantByName(name);
        break;
    }
    case 3:
    {
        int age;
        cout << "Enter Age to search: ";
        cin >> age;
        list.searchTenantByAge(age);
        break;
    }
    case 4:
    {
        tm lastLogin;
        cout << "Enter Last Login date (format: dd mm yyyy): ";
        cin >> lastLogin.tm_mday >> lastLogin.tm_mon >> lastLogin.tm_year;
        lastLogin.tm_mon -= 1;     // tm_mon is months since January - [0,11]
        lastLogin.tm_year -= 1900; // tm_year is years since 1900
        list.searchTenantByLastLogin(lastLogin);
        break;
    }
    default:
        cout << "Invalid choice. Please enter a number between 1 and 4.\n";
    }
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

void Tenant::tenantMenu()
{
    string choice; 
    PropertyLinkedList propertyList;
    readProperties(propertyList);

    do
    {
        cout << "\nTenant's Realm: \n";
        cout << "1. Sort and unveil the secrets of property information\n";
        cout << "2. Seek and reveal property details through the digital maze\n";
        cout << "3. Save a special property, a cozy corner of your world\n";
        cout << "4. Send forth your rent request like a virtual carrier pigeon\n";
        cout << "5. Trace the path of property history through the annals of time\n";
        cout << "6. Logout\n";
        cout << "Your Move, O' Inhabitant. " << endl << "Choose Wisely:";

        cin >> choice;

        if (choice == "1")
        {
            propertyList.display();
        }
        else if (choice == "2")
        {
            // Call function to sort properties
        }
        else if (choice == "3")
        {
            // Call function to search property
        }
        else if (choice == "4")
        {
            // Call function to save favorite property
        }
        else if (choice == "5")
        {
            // Call function to place rent request
        }
        else if (choice == "6")
        {
            cout << "Escaping...\n";
        }
        else
        {            
            cout << "Ah, the land of indecision! Enter a realm between 1 and 6, mortal.\n";
        }
    } while (choice != "6");  // This condition should check against a string
}
