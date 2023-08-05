#include "manager.h"
#include "user_types.h" // If needed
#include <iostream>

void managerMenu() {
    int choice;
    do {
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

        switch (choice) {
            case 1:
                // Call function to display tenant details
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